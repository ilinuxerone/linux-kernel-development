#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");

extern struct bus_type my_bus_type;

static int my_probe(struct device *dev)
{
	printk("<0>Driver find device which my driver can handle!");
	return 0;
}

static int my_remove(struct device *dev)
{
	printk("<0>Driver found device uploaded!");
	return 0;
}

static ssize_t  mydriver_show(struct device_driver *driver, struct driver_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", "This is my driver!");	
}

DRIVER_ATTR(drv, S_IRUGO, mydriver_show, NULL);

struct device_driver my_driver = {
    .name = "my_dev",
    .bus = &my_bus_type,
    .probe = my_probe,
    .remove = my_remove,
};

static int __init my_driver_init(void)
{
    int ret;

    ret = driver_register(&my_driver);
    if (ret){
	printk(KERN_ALERT "register driver failed\n");
	return ret;
    }

    driver_create_file(&my_driver, &driver_attr_drv);
    return ret;
}

static void __exit my_driver_exit(void)
{
    driver_unregister(&my_driver);
}

module_init(my_driver_init);
module_exit(my_driver_exit);
