#include <linux/init.h>				/* for module */
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/kernel.h> 			/* printk() */
#include <linux/slab.h>				/* kmalloc() */
#include <linux/fs.h>				/* everything... */
#include <linux/errno.h>			/* error codes */
#include <linux/types.h>			/* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>			/* O_ACCMODE */
#include <linux/seq_file.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <asm/uaccess.h>			/* copy_*_user */

#include "scull.h"					/* local definitions */

int scull_major		= SCULL_MAJOR;
int scull_minor 	= 0;
int scull_nr_devs 	= SCULL_NR_DEVS;
int scull_quantum	= SCULL_QUANTUM;
int scull_qset		= SCULL_QSET;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);
module_param(scull_qset, int, S_IRUGO);

struct scull_dev* scull_device;
struct class* scull_device_class;
struct device* scull_device_file;


int scull_trim(struct scull_dev* dev) {
	struct scull_qset* next, *dptr;
	int qset = dev->qset;							/* the dev must be not-null */
	int i;

	for (dptr = dev->data; dptr; dptr = next) {
		if (dptr->data) {							/* if dptr->data != NULL */
			for (i = 0; i > qset; i++) 
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}

	/* for trim */
	dev->size 		= 0;
	dev->quantum 	= scull_quantum;
	dev->qset 		= scull_qset;
	dev->data		= NULL;
	return 0;
}

/* open and close */
int scull_open(struct inode* inode, struct file* filp) {
	struct scull_dev* dev;							/* the device information */

	/* use container_of to gain the cdev pointer and give dev->cdev */
	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev;						/* to store the device information */

	/* if open to write, trim the device to 0 length */
	if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
		/* need to lock */
		if (down_interruptible(&dev->sem)) {
			return -ERESTARTSYS;
		}
		scull_trim(dev);
		/* need to unlock */
		up(&dev->sem);
	}
	return 0;
}

int scull_release(struct inode* inode, struct file* filp) {
	return 0;
}

struct scull_qset* scull_follow(struct scull_dev* dev, int n) {
	struct scull_qset* qs = dev->data;				/* gain the list header */
	
	/* allocate first qset if need be */
	if (!qs) {										/* if qs == NULL */
		qs = dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (qs == NULL) 							/* allocate error */
			return NULL;
		memset(qs, 0, sizeof(struct scull_qset));
	}

	/* start to find */
	while (n--) {
		if (!qs->next) {							/* qs->next	== NULL */
			qs->next = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
			if (qs->next == NULL)
				return NULL;
			memset(qs->next, 0, sizeof(struct scull_qset));
		}
		qs = qs->next;
	}
	return qs;
}

/*
*			↓			 →	   quantum    ←
*			q	quantum0: |//////////////|
*			s	quantum1: |//////////////|
*			e	quantum2: |//////////////|
*			t	quantum3: |///////		 | ← s_pos
*			↑					 ↑
*								 q_pos
*/
ssize_t scull_read(struct file* filp, char __user* buf, size_t count, loff_t* f_pos) {
	struct scull_dev* dev = filp->private_data;		/* device data */
	struct scull_qset* dptr;						/* for data list */
	int quantum = dev->quantum, qset = dev->qset;
	int item_size = quantum * qset;					/* the totally byte in list_item */
	int item, s_pos, q_pos, rest;
	ssize_t ret_val = 0;

	/* need to lock */
	if (down_interruptible(&dev->sem)) 
		return -ERESTARTSYS;
	
	if (*f_pos >= dev->size) 						/* the pos start over the size */
		goto out;
	if (*f_pos + count > dev->size)					/* the read size over the size */
		count = dev->size - *f_pos;

	/* to find data pos where can read start */
	item = (long)*f_pos / item_size;				/* the Nth node */
	rest = (long)*f_pos % item_size;				/* the quantum of the Nth node */
	s_pos = rest / quantum, q_pos = rest % quantum;	/* the s_pos is quantumN just like shown above */

	/* to find the right position in list */
	dptr = scull_follow(dev, item);
	if (dptr == NULL || !dptr->data || !dptr->data[s_pos])
		goto out;

	if (count > quantum - q_pos) 					/* read count can't over quantum only end it */
		count = quantum - q_pos;

	/* start read data from kern_space to user_space */
	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
		ret_val = -EFAULT;
		goto out;
	}

	*f_pos += count;								/* update the f_pos */
	ret_val = count;
	
out:
	/* need unlock */
	up(&dev->sem);
	return ret_val;
}

ssize_t scull_write(struct file* filp, const char __user* buf, size_t count, loff_t* f_pos) {
	struct scull_dev* dev = filp->private_data;
	struct scull_qset* dptr;
	int quantum = dev->quantum, qset = dev->qset;
	int item_size = quantum * qset;					/* the totally byte in list_item */
	int item, s_pos, q_pos, rest;
	ssize_t ret_val = -ENOMEM;

	/* need to lock */
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	
	/* to find data pos where can read start */
	item = (long)*f_pos / item_size;				/* the Nth node */
	rest = (long)*f_pos % item_size;				/* the quantum of the Nth node */
	s_pos = rest / quantum, q_pos = rest % quantum; /* the s_pos is quantumN just like shown above */

	/* to find the right position in list */
	dptr = scull_follow(dev, item);
	if (dptr == NULL)
		goto out;

	if (!dptr->data) {
		dptr->data = kmalloc(qset * sizeof(char*), GFP_KERNEL);
		if (!dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(char*));
	}	
	if (!dptr->data[s_pos]) {
		dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
		if (!dptr->data[s_pos])
			goto out;
	}

	/* write only up to the end of quantum */
	if (count > quantum - q_pos)
		count = quantum - q_pos;

	/* start to write from user_space to kern_space */
	if (copy_from_user(dptr->data[s_pos], buf, count)) {
		ret_val = -EFAULT;
		goto out;
	}

	*f_pos += count;									/* update f_pos */
	ret_val = count;
	
out:
	/* need to unlock */
	up(&dev->sem);
	return ret_val;
}

struct file_operations scull_ops = {
	.owner		= THIS_MODULE,
	.read		= scull_read,
	.write		= scull_write,
	.open		= scull_open,
	.release	= scull_release,
};

// struct proc_ops scull_proc_ops;

void scull_cleanup_module(void) {
	int i;
	dev_t devno;

	/* clean device */
	for (i = 0; i < scull_nr_devs; i++) {
		devno = MKDEV(scull_major, scull_minor + i);
		device_destroy(scull_device_class, devno);
	}

	/* clean class */
	class_destroy(scull_device_class);

	/* clean cdev structure */
	if (scull_device) {
		for (i = 0; i < scull_nr_devs; i++) {
			scull_trim(scull_device + i);
			cdev_del(&scull_device[i].cdev);
		}
		kfree(scull_device);
	}

	/* clean register cdev structure */
	unregister_chrdev_region(devno, scull_nr_devs);
}

/* setup the char_dev structure for this device */
static void scull_setup_cdev(struct scull_dev* dev, int index) {
	// printk(KERN_ALERT "start to setup cdev structure\n");
	int err, devno = MKDEV(scull_major, scull_minor + index); /* because scull0 ~ scull3 */
	char device_name[7] = {"scull"};
	// printk(KERN_ALERT "\tthe devno: %d\tindex:%d\n", devno, index);

	cdev_init(&dev->cdev, &scull_ops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops	= &scull_ops;
	
	err = cdev_add(&dev->cdev, devno, 1);
	if (err) {
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
	}
	
	device_name[5] = (char)(index + 48), device_name[6] = '\0';

	scull_device_file = device_create(scull_device_class, NULL, devno, NULL, device_name);
	printk(KERN_ALERT "devno major: %d, minor: %d, %s\n", MAJOR(devno), MINOR(devno), device_name);
	if (IS_ERR(scull_device_class)) {
		printk(KERN_ERR "scull: can't create a device file\n");
	}
	// printk(KERN_ALERT "end to setup\n");
}

int scull_init_module(void) {
	printk(KERN_ALERT "entry the scull_init_module\n");
	int result, i;
	dev_t dev = 0;

	/* to get dynamic major unless directed otherwise at load time */
	if (scull_major) { /* if the major set by user not default */
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, scull_nr_devs, "scull");
	} else {
		/* dynamic major */
		printk(KERN_ALERT "start dynamic create major:\n\t");
		result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
		scull_major = MAJOR(dev); /* use MAJOR gain the major number */
		printk(KERN_ALERT "scull_major: %d\t scull_minor: %d\t result: %d\n", scull_major, scull_minor, result);
	}
	if (result < 0) {
		printk(KERN_WARNING	"scull: can't get major %d\n", scull_major);
		return result;
	}

	/* allocate the device */
	scull_device = kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
	if (!scull_device) {
		result = -ENOMEM;
		goto fail;
	}
	memset(scull_device, 0, scull_nr_devs * sizeof(struct scull_dev));

	/* create device class */
	scull_device_class = class_create(THIS_MODULE, "scull_class");
	if (IS_ERR(scull_device_class)) {
		printk(KERN_ERR "scull: can't create a device class\n");
		result = -EFAULT;
	}
	
	/* for initialize each device */
	for (i = 0; i < scull_nr_devs; i++) {
		scull_device[i].quantum = scull_quantum;
		scull_device[i].qset 	= scull_qset;
		/* Note: in 5.15 kernel init_MUTEX del use sema_init(sem, val) */
		sema_init(&scull_device[i].sem, 1);
		scull_setup_cdev(&scull_device[i], i);
	}

	/* for any device */
	dev = MKDEV(scull_major, scull_minor);
	
fail:
	scull_cleanup_module();
	return result;
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GPL");
