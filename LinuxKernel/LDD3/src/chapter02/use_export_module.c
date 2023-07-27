#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

extern int module_function(void);

static int use_module_function(void) {
	module_function();
	printk(KERN_ALERT "this is use_module_function\n");
	return 0;
}

static int __init use_module_init(void) {
	printk(KERN_ALERT "use module init\n");
	use_module_function();
	return 0;
}

static void __exit use_module_exit(void) {
	printk(KERN_ALERT "use module exit\n");
}

module_init(use_module_init);
module_exit(use_module_exit);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GPL");
