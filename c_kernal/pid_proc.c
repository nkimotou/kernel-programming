
#include "pid_proc.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int my_proc_show(struct seq_file *m, void *v) {
    seq_printf(m, "Current PID: %d\n", current->pid);
    return 0;
}

static int my_proc_open(struct inode *inode, struct  file *file) {
    return single_open(file, my_proc_show, NULL);
}

static const struct file_operations my_proc_fops = {
        .owner = THIS_MODULE,
        .open = my_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};

static int __init proc_init(void) {
    proc_create("myproc", 0, NULL, &my_proc_fops);
    return 0;
}

static void __exit proc_exit(void) {
    remove_proc_entry("myproc", NULL);
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Proc file system example");
MODULE_VERSION("0.1");
