#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static char *version = "version 1.0";

static int my_match(const struct device *dev, struct device_driver *driver)
{
    return !strncmp(dev_name(dev), driver->name, strlen(driver->name));
}

static ssize_t show_bus_version(struct bus_type *bus, char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%s\n", version);
}
static BUS_ATTR(version, S_IRUGO, show_bus_version, NULL);

static struct bus_type my_bus_type = {
	.name = "my_bus",
	.match = my_match,
};

static int __init my_bus_init(void)
{
    int ret;
    
    ret = bus_register(&my_bus_type);
    if (ret)
	 goto ret;
    if (bus_create_file(&my_bus_type, &bus_attr_version))
        printk("<0> failed to create version attribute!\n");
ret:      
    return ret;
}

static void __exit my_bus_exit(void)
{
   bus_unregister(&my_bus_type); 
}

module_init(my_bus_init);
module_exit(my_bus_exit);

