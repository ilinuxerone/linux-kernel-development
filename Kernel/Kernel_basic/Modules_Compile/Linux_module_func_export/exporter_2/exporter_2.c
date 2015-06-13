#include <linux/init.h>
#include <linux/module.h> 
#include<linux/kernel.h>

static void exported_function_2(void)
{
	printk(KERN_ALERT "I'm %s ！(in %s)\n", __func__, __FILE__);
	return;
}

static int __init exporter_2_init(void)
{
	printk(KERN_ALERT "Hello, Tekkaman Ninja ！\nexported_function_2 is online!\n");
	return 0;
}

static void __exit exporter_2_exit(void)
{
	printk(KERN_ALERT "Goodbye, Tekkaman Ninja ！\nexported_function_2 is gone!\n");
}

module_init(exporter_2_init);
module_exit(exporter_2_exit);

EXPORT_SYMBOL(exported_function_2);

MODULE_DESCRIPTION("Module function exporting's exporter_2 test module");
MODULE_VERSION("v1.0");
MODULE_AUTHOR("Tekkaman Ninja");
MODULE_LICENSE("Dual BSD/GPL");
