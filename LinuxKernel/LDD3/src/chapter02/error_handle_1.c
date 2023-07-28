#include "linux/init.h"
#include "linux/errno.h"
#include "linux/kernel.h"
#include "linux/module.h"

int register_this(const char* module, const char* name) {
    printk(KERN_ALERT "module: %s -> %s(init success)!\n", module, name);
    return 0;
}

int register_that(const char* module, const char* name) {
    printk(KERN_ALERT "module: %s -> %s(init success)!\n", module, name);
    return 0;
}

int register_those(const char* module, const char* name) {
    printk(KERN_ALERT "module: %s -> %s(init success)!\n", module, name);
    return 0;
}

void unregister_this(const char* module, const char* name) {
    printk(KERN_ALERT "module: %s -> %s(release success)!\n", module, name);
}

void unregister_that(const char* module, const char* name) {
    printk(KERN_ALERT "module: %s -> %s(release success)!\n", module, name);
}

void unregister_those(const char* module, const char* name) {
    printk(KERN_ALERT "module: %s -> %s(release success)!\n", module, name);
}


static __init int my_init_function(void) {
    int err;

    err = register_this("hello", "nice");
    if (err) goto fail_this;
    err = register_that("world", "nice");
    if (err) goto fail_that;
    err = register_those("c language", "nice");
    if (err) goto fail_those;
    return 0;

fail_those:
    unregister_those("c language", "bad");
	return EBADHANDLE;
fail_that:
    unregister_that("world", "bad");
	return EBADHANDLE;
fail_this:
    unregister_this("hello", "bad");
	return EBADHANDLE;
}

static __exit void my_clean_function(void) {
    unregister_those("c language", "nice");
    unregister_that("world", "nice");
    unregister_that("hello", "nice");
}

module_init(my_init_function);
module_exit(my_clean_function);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GLP");
