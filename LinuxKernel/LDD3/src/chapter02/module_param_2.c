#include "linux/init.h"
#include "linux/kernel.h"
#include "linux/module.h"
#include "linux/moduleparam.h"

#define MAX_SIZE 10

int sum = 0;
static char* whom = "myself";
static int num_array[MAX_SIZE];
static int array_size;

module_param(whom, charp, S_IRUGO);
module_param_array(num_array, int, &array_size, S_IRUGO);

static __init int init_function(void) {
    printk(KERN_ALERT "enter init\n");
    for (int i = 0; i < array_size; i++) {
        sum += num_array[i];
    }
    printk(KERN_ALERT "%s called sum -> %d\n", whom, sum);
    return 0;
}

static __exit void exit_function(void) {
    printk(KERN_ALERT "enter exit\n");
}

module_init(init_function);
module_exit(exit_function);

MODULE_AUTHOR("Miao");
MODULE_LICENSE("Dual BSD/GLP");
