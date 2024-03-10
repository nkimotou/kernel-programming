
#include "device_driver.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DEVICE_NAME "mychardev"

static int major_num;

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
printk(KERN_INFO "Read from device\n");
return 0;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
printk(KERN_INFO "Write to device\n");
return len;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static struct file_operations fops = {
        .open = my_open,
        .read = my_read,
        .write = my_write,
        .release = my_release,
};

static int __init chardev_init(void) {
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_num < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_num;
    }
    printk(KERN_INFO "Registered correctly with major number %d\n", major_num);
    return 0;
}

static void __exit chardev_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Unregistered the device\n");
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple character device driver");
MODULE_VERSION("0.1");
