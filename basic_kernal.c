#include "basic_kernal.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// This function is called when the module is loaded
static int __init hello_init(void) {
    printk(KERN_INFO "Hello, kernel!\n");
    return 0; // Success
}

// This function is called when the module is unloaded
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, kernel!\n");
}

// Macros to specify the initialization and exit functions
module_init(hello_init);
module_exit(hello_exit);

// Information about the module
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple example Linux module");
MODULE_VERSION("0.1");
