#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhihong");
MODULE_DESCRIPTION("cdev");

int hello_major = 555;
int hello_minor = 0;
int number_of_devices = 1;

struct cdev cdev;
dev_t 	dev = 0;

struct file_operations hello_fops = {
	.owner = THIS_MODULE,
};

static void char_reg_setup_cdev(void)
{
	int error, devno = MKDEV(hello_major, hello_minor);
	cdev_init(&cdev, &hello_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &hello_fops;
	error = cdev_add(&cdev, devno, 1);
	if (error) {
		printk(KERN_NOTICE "Error %d adding char_reg_setup_cdev", error);
	}
}


struct class *my_class;
	
static 	int __init hello_2_init(void)
{
	int result;
	
	dev = MKDEV(hello_major, hello_minor);
	result = register_chrdev_region(dev, number_of_devices, "hello");
	if (result ) {
		printk(KERN_WARNING "hello: can't get major number %d\n", hello_major);
		return result;
	}
	
	char_reg_setup_cdev();
	
/*create your own class under /sysfs*/
my_class = class_create(THIS_MODULE, "my_class");
if (IS_ERR(my_class)){
	printk(KERN_ERR "failed in creating class.\n");
	return -1;
}

/*register your own device in sysfs. and this will cause udev to create corresponding device node*/
device_create(my_class, NULL, MKDEV(hello_major, 0),NULL, "hello" "%ds",  0); ///////

printk(KERN_INFO "register character driver\n");

return 0;
}

static void __exit hello_2_exit(void)
{
	dev_t  devno = MKDEV(hello_major, hello_minor);
	
	cdev_del(&cdev);
	
	device_destroy(my_class, MKDEV(hello_major, 0));
	class_destroy(my_class);
	
	unregister_chrdev_region(devno, number_of_devices);
	
	printk(KERN_INFO "char driver cleaned up\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);

