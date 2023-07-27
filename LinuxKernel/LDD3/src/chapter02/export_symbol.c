#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int module_function(void) {
	printk(KERN_ALERT "EXPORT SYMBOL	In Func: %s...\n", __func__);
    return 0;
}

EXPORT_SYMBOL(module_function);

static int __init export_symbol_init(void) {
	printk(KERN_ALERT "EXPORT SYMBOL	Module one, Init!\n");
    return 0;
}

static void __exit export_symbol_exit(void) {
	printk(KERN_ALERT "EXPORT SYMBOL	Module one, Exit!\n");
}

module_init(export_symbol_init);
module_exit(export_symbol_exit);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GPL");
