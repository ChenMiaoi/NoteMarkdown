#include "linux/init.h"
#include "linux/errno.h"
#include "linux/kernel.h"
#include "linux/module.h"

#define SUCCESS 1
#define FAIL 0

int item1, item2, stuff_ok;

int allocate_item(const char* item) {
    printk(KERN_ALERT "%s allocate -> success!\n", item);
    return SUCCESS;
}

void release_item(const char* item) {
    printk(KERN_ALERT "%s release -> success!\n", item);
}

int register_stuff(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
        printk(KERN_ALERT "register [%s] -> success!\n", va_arg(args, const char*));
    va_end(args);
    return 0;
}

void unregister_stuff(void) {
    if (item1) printk(KERN_ALERT "release [item1] -> success!\n");
    if (item2) printk(KERN_ALERT "release [item2] -> success!\n");
}

void my_cleanup(void) {
    if (item1) release_item("item1");
    if (item2) release_item("item2");
    if (stuff_ok) unregister_stuff();
}

static __init int my_init(void) {
    int err = ENOMEM;
    item1 = allocate_item("item1");
    item2 = allocate_item("item2");

    if (!item1 || !item2) goto fail;
    err = register_stuff(2, "item1", "item2");
    if (!err) stuff_ok = 1;
    else goto fail;
    printk(KERN_ALERT "success init!\n");

    return 0;
fail:
    my_cleanup();
    return err;
}

static __exit void my_exit(void) {
    my_cleanup();
    printk(KERN_ALERT "success exit!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GLP");
