#include "linux/init.h"
#include "linux/kernel.h"
#include "linux/module.h"
#include "linux/moduleparam.h"

static char* whom = "myself";
static int howmany = 1;

module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

static __init int init_function(void) {
    printk(KERN_ALERT "enter init\n");
    for (int i = 0; i < howmany; i++) {
        printk(KERN_ALERT "%s called -> %d\n", whom, i);
    }
    return 0;
}

static __exit void exit_function(void) {
    printk(KERN_ALERT "enter exit\n");
}

module_init(init_function);
module_exit(exit_function);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GLP");
