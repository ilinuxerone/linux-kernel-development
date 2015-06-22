#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


static int test;
module_param(test, int, 0644);

static  int  __init hello_init(void)
{
	printk(KERN_ALERT "hello, world, from kernel space... test= %d\n", test);
	return 0;
}

static void __exit hello_cleanup(void)
{
	printk(KERN_ALERT "goodbye, leaving from kernel...\n");
}


module_init(hello_init);
module_exit(hello_cleanup);


