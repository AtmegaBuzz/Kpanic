#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/kdev_t.h>





/* Meta Information */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SWAPNIL SHINDE");
MODULE_DESCRIPTION("THIS IS GREETHING MODULE");

// creating dev with our custom major and minor number
// dev_t dev = MKDEV(494,0);
dev_t dev = 0;

static struct class *dev_class;



/* open and close a file using linux driver */
// int myNumber, arr_numbers[4];
// char *charValue;
// int cb_value = 0;


// module_param(myNumber,int,S_IRUSR|S_IWUSR);
// module_prarm(charValue,charp,S_IRUSR|S_IWUSR);
// module_param_array(arr_numbers,int,NULL,S_IRUSR|S_IWUSR);

static int __init ModuleInit(void){

  // static method of assigning major and minor number
  // register_chrdev_region(dev,1,"Embedded dev device");

  int res = alloc_chrdev_region(&dev,0,1,"Embedded devices 1");

  if (res < 0){
    pr_info("Major Number allocation failed\n");
    return -1;
  }

  // creating struct class

  if ( (dev_class = class_create(THIS_MODULE,"ext_class")) == NULL ) {
      pr_err("Cannot create the struct class for the device\n");
      goto r_class;
  }

  if ( (device_create(dev_class,NULL,dev,NULL,"ext_class")) == NULL ){
    pr_err("Cannot create device\n");
    goto r_device;
  }
    
  pr_info("Major Number %d, Minor Number %d\n",MAJOR(dev),MINOR(dev));
  return 0;

r_device:
  class_destroy(dev_class);

r_class:
  unregister_chrdev_region(dev,1);
  return -1;
  
}


static void __exit ModuleExit(void){

  unregister_chrdev_region(dev,1);

  // remove device file from /proc/devices
  device_destroy(dev_class,dev);
  class_destroy(dev_class);
  pr_info("module exit\n");  
}


module_init(ModuleInit);
module_exit(ModuleExit);