
#include "kernel_timer.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

static struct timer_list my_timer;

static void timer_callback(struct timer_list *timer) {
    printk(KERN_INFO "Timer expired!\n");
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000)); // Reschedule timer
}

static int __init timer_init(void) {
    printk(KERN_INFO "Timer module loaded\n");
    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000)); // Start timer
    return 0;
}

static void __exit timer_exit(void) {
    del_timer(&my_timer); // Delete timer when unloading module
    printk(KERN_INFO "Timer module unloaded\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel timer example");
MODULE_VERSION("0.1");
