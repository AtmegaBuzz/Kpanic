#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int __init kpanic_init(void) {
    printk(KERN_INFO "Kernel Panic module initialized.\n");
    panic("Kernel panic triggered from kpanic module.");
    return 0;
}

static void __exit kpanic_exit(void) {
    printk(KERN_INFO "Kernel Panic module exited.\n");
}
module_init(kpanic_init);
module_exit(kpanic_exit);

