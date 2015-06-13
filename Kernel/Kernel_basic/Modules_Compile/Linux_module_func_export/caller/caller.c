#include <linux/init.h>
#include <linux/module.h> 
#include<linux/kernel.h>
extern void exported_function_1(void);
extern void exported_function_2(void);

static int __init caller_init(void)
{
	printk(KERN_ALERT "Hello, Tekkaman Ninja ！\nNow call exporters's function!\n");
	exported_function_1();
	exported_function_2();
	return 0;
}

static void __exit caller_exit(void)
{
        printk(KERN_ALERT "Goodbye, Tekkaman Ninja ！\n");
}

module_init(caller_init);
module_exit(caller_exit);


MODULE_DESCRIPTION("Module function exporting's caller test module");
MODULE_VERSION("v1.0");
MODULE_AUTHOR("Tekkaman Ninja");
MODULE_LICENSE("Dual BSD/GPL");
