#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static const struct proc_dir_entry* ety;

static int test_seq_proc_show(struct seq_file* m, void* v) {
	printk(KERN_ALERT "proc ops: read handle\n");
	seq_printf(m, "Device: test_proc\tStatus: success\r\n\tVersion: 0.1.0\n");
	return 0;
}

static void* test_seq_proc_start(struct seq_file* m, loff_t* pos) {
	return m;
}

static void test_seq_proc_stop(struct seq_file* m, void* v) {
}

static void* test_seq_proc_next(struct seq_file* m, void* v, loff_t* pos) {
	return NULL;
}

static struct seq_operations test_seq_ops = {
	.start	= test_seq_proc_start,
	.next 	= test_seq_proc_next,
	.stop 	= test_seq_proc_stop,
	.show 	= test_seq_proc_show,
};

static int test_proc_open(struct inode* ind, struct file* filp) {
	return single_open(filp, test_seq_proc_show, NULL);
	// return seq_open(filp, &test_seq_ops);
}

/* 一般的，我们通常使用seq_read，而不是自己写的read */
static ssize_t test_proc_read(struct file* filp, char __user* buf, size_t count, loff_t* pos) {
	printk(KERN_ALERT "proc ops: read handle\n");
	return 0;
}

/* proc一般是只读的，因此也不需要实现write ops */
static ssize_t test_proc_write(struct file* filp, const char __user* buf, size_t count, loff_t* pos) {
	printk(KERN_ALERT "proc ops: write handle\n");
	return 0;
}

static struct proc_ops test_proc_ops = {
	.proc_open    = test_proc_open,
	.proc_read    = seq_read,
	// .proc_write	  = test_proc_write,
	.proc_lseek   = seq_lseek,
	.proc_release = single_release,
};

static __init int test_proc_init(void) {
	printk(KERN_ALERT "entry the proc init\n");
	ety = proc_create("test_proc", 0, NULL, &test_proc_ops);
	printk(KERN_ALERT "done the proc init\n");
	return 0;
}

static __exit void test_proc_exit(void) {
	printk(KERN_ALERT "entry the proc exit\n");
	proc_remove(ety);
	printk(KERN_ALERT "done the proc remove\n");
}

module_init(test_proc_init);
module_exit(test_proc_exit);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GLP");

