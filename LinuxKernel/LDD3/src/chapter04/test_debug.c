#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static __init int test_debug_init(void) {
	printk(KERN_ALERT "entry init func\n");
	printk(KERN_DEBUG "This is debug message in [%s] at [%d] lines\n"
		, __FILE__, __LINE__);
	return 0;
}

static __exit void test_debug_exit(void) {
	printk(KERN_ALERT "entry exit func\n");
	printk(KERN_DEBUG "This is debug message in [%s] at [%d] lines\n"
		, __FILE__, __LINE__);
}

module_init(test_debug_init);
module_exit(test_debug_exit);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GPL");
