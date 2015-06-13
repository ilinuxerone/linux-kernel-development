#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

extern struct device my_bus_device;
extern struct bus_type my_bus_type;

static void my_dev_release(struct device *dev)
{
    printk("my_device_release called~\n");	
}

struct device my_dev = {
    .bus = &my_bus_type,
    .parent = &my_bus_device,
    .release = my_dev_release,

};

static ssize_t mydev_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", "This is my device!");
}

static DEVICE_ATTR(dev, S_IRUGO, mydev_show, NULL);

static int __init my_device_init(void)
{
    int ret = 0;

    dev_set_name(&my_dev, "my_dev");
    device_register(&my_dev);

    device_create_file(&my_dev, &dev_attr_dev);

    return ret;
}



static void __exit my_device_exit(void)
{
    device_unregister(&my_dev);
}

module_init(my_device_init);
module_exit(my_device_exit);
