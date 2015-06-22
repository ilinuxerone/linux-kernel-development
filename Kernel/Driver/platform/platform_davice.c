#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhihong");
MODULE_DESCRIPTION("platform_device");
MODULE_VERSION("version 1.0");

static struct platform_device *my_device;

static int __init my_device_init(void)
{
	int ret = 0;
	
	my_device = platform_device_alloc("my_dev" ,-1);
	
	ret = platform_device_add(my_device);
	if (ret){
		platform_device_put(my_device);
	}//出错了要撤销以前的工作，这个很重要。
	
	return ret;
}

static void __exit my_device_exit(void)
{
	platform_device_unregister(my_device);
}


module_init(my_device_init);
module_exit(my_device_exit);

