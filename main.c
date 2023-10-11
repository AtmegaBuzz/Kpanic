#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/keyboard.h>

MODULE_AUTHOR("Swapnil Shinde");
MODULE_DESCRIPTION("Simple driver that logs keyboard stokes in the kernel log");
MODULE_LICENSE("GPL");


static int my_keyboard_notifier(struct notifier_block *nblock,unsigned long code, void *_param){
  struct keyboard_notifier_param *param = _param;

  if ( code == KBD_KEYCODE ){
    pr_info("Key Pressed (Key=%u)\n",param->value);
  }

  return NOTIFY_OK;
}


static struct notifier_block my_keyboard_notifier_block = {
  .notifier_call = my_keyboard_notifier,
};


static int __init init_keyboard(void){


  pr_info("Loaded Keyboard Module");
  register_keyboard_notifier(&my_keyboard_notifier_block);
  return 0;
}


static void __exit exit_keyboard(void){
  unregister_keyboard_notifier(&my_keyboard_notifier_block);
  pr_info("Keyboard module removed");
  
}


module_init(init_keyboard);
module_exit(exit_keyboard);