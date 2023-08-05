#ifndef __SCULL_H__
#define __SCULL_H__

#undef PDEBUG
#ifdef SCULL_DEBUG
	#ifdef __KERNEL__
		#define PDEBUG(fmt, args...) printk(KERN_DEBUG "scull: " fmt, ## args)
	#else
		#define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
	#endif // !__KERNEL__
#else
	#define PDEBUG(fmt, args...) 	/* nothing to do */
#endif // !SCULL_DEBUG

#undef PDEBUGG
#define PDEBUGG(fmt, args...) 		/* nothing to do */

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0				/* dynamic major number by default */
#endif // !SCULL_MAJOR

#ifndef SCULL_NR_DEVS
#define SCULL_NR_DEVS 4				/* scull0 ~ scull4 */
#endif // !SCULL_NR_DEVS

#ifndef SCULL_P_NR_DEVS
#define SCULL_P_NR_DEVS 4			/* scull_pipe0 ~ scull_pipe3 */
#endif // !SCULL_P_NR_DEVS

/**
* scull_qset->data: void** data -> data[qset][quantum]
* 
*			↓			 →	   quantum    ←
*			q	quantum0: |//////////////|
*			s	quantum1: |//////////////|
*			e	quantum2: |//////////////|
*			t	quantum3: |///////		 | ←
*			↑					 ↑
*							
**/
#ifndef SCULL_QUANTUM
#define SCULL_QUANTUM 4000
#endif // !SCULL_QUANTUM

#ifndef SCULL_QSET
#define SCULL_QSET 1000
#endif // !SCULL_QSET

#ifndef SCULL_P_BUFFER
#define SCULL_P_BUFFER 4000
#endif // !SCULL_P_BUFFER

struct scull_qset {
	void** data;
	struct scull_qset* next;
};

/**
* scull_dev->data →→→→→→ →→→→→→ →→→→→→ scull_dev->data->next->data →→→→→→ →→→→→→ →→→→→→ end
*			  ↓												   ↓
*			  ↓→ |////////////////|							   ↓→ |////////////////| quantum0
*			  ↓												   ↓
*			  ↓→ |////////////////|							   ↓→ |////////////////| quantum1
*			  ↓												   ↓
*			  ↓→ |////////////////|							   ↓→ |////////////////| quantum2
*			  ↓												   ↓
* 			  ↓→ |////////////////|							   ↓→ |////////////////| quantum3
**/
struct scull_dev {
	struct scull_qset* data;		/* pointer to first quantum set */
	int quantum;					/* the current quantum size */
	int qset;						/* the current array size */
	unsigned long size;				/* amount of data stored */
	unsigned int access_key;		/* used by sculluid and scullpriv */
	struct semaphore sem;			/* mutual exclusion semaphore */
	struct cdev cdev;				/* char device structure */
};

/* to split minors in two parts */

/* the different configurable params */
extern int scull_major;				/* main.c */
extern int scull_nr_devs;
extern int scull_quantum;
extern int scull_qset;

#endif // !__SCULL_H__
