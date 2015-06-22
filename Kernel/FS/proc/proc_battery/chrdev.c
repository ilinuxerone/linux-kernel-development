#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/io.h>
#include <linux/timer.h>
#include <linux/device.h>

struct demo_cdev{
	struct cdev   cdev;
	struct        semaphore sem;
	char          *buf;
}demo_cdev;

static dev_t devno = 0;
struct proc_dir_entry  *proc_power;
struct proc_dir_entry  *proc_power_status;
struct proc_dir_entry  *proc_power_mode;

struct timer_list  timer;
char  mode_buf[1024];
char  status_buf[1024];

struct class *battery_class;

struct  battery {
	int  status;
	int   mode;
};

struct battery  init_battery = {
	.status =  100,
	.mode   =  0,
};

void switch_mode(void)
{
	int flag;

	flag = init_battery.status % 10;
	switch (flag) {
		case 0:
			init_battery.mode = 1;
			break;
		default:
			init_battery.mode = 0;
			break;
	}
}

void timer_func(int arg)
{
	printk(KERN_INFO "Calling timer_func...\n");
	if (--init_battery.status){
		printk("battery status %d\n", init_battery.status);
		switch_mode();
	}else {
		printk(KERN_EMERG "Battery is running out...\n");
		printk(KERN_EMERG "Reset status\n");
		init_battery.status = 100;
	}	

	mod_timer(&timer,jiffies +  5 * HZ);
}


int demo_cdev_open(struct inode *inode, struct file *filp)
{
	struct demo_cdev	*dev;
	
	dev = container_of(inode->i_cdev, struct demo_cdev, cdev);
	filp->private_data = dev;

	printk("demo_chrdev_open\n");
	return 0;

}

int demo_cdev_release(struct inode *inode, struct file *filp)
{
	printk("demo_chrdev_released\n");
	return 0;
}

int demo_cdev_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long args)
{
	printk("demo_chrdev_ioctl\n");
	return 0;

}

struct file_operations  demo_cdev_ops = {
	.owner = THIS_MODULE,
	.open = demo_cdev_open,
	.release = demo_cdev_release,
	.ioctl  = demo_cdev_ioctl,
	.read   = NULL,
	.write = NULL,
};

int proc_read_status(char *page, char **stat, off_t off, int count,
			int *peof, void *data)
{
	int len;

	snprintf(status_buf,1024, "%d\n", init_battery.status );
	len = strlen(status_buf);

	if (off >= len)
		return 0;

	if (count > len - off)
		count = len - off;
	memcpy(page + off, status_buf + off, count);

	return off + count;
}

int proc_read_mode(char *page, char **stat, off_t off, int count,
			int *peof, void *data)
{
	int len ;

	snprintf(mode_buf,1024, "%d\n", init_battery.mode);
	 len = strlen(mode_buf);

	if (off >= len)
		return 0;

	if (count > len - off)
		count = len - off;
	memcpy(page + off, mode_buf + off, count);

	return off + count;
}

static int __init demo_module_init(void)
{
	int  ret;
	
	ret = alloc_chrdev_region(&devno, 0, 1, "demo_chrdev");
	if (ret < 0) {
		printk(KERN_WARNING "demo: can't get major \n");
		return ret;
	}
	
        cdev_init(&demo_cdev.cdev, &demo_cdev_ops);
	demo_cdev.cdev.owner = THIS_MODULE;
	demo_cdev.cdev.ops = &demo_cdev_ops;
	ret = cdev_add(&demo_cdev.cdev, devno, 1);
	if (ret){
		printk(KERN_ERR "Error:%d adding  demo_cdev\n", ret); 
	}
	demo_cdev.buf = kmalloc(1024, GFP_KERNEL);
	if (!demo_cdev.buf){
		printk(KERN_ERR "no mem for demo_cdev\n");
		return -ENOMEM;
	}
	memset(demo_cdev.buf, 0, 1024);

	/*create your own class under /sysfs*/

	battery_class = class_create(THIS_MODULE, "battery_supply");
	if (IS_ERR(battery_class)){
		printk(KERN_ERR "failed in creating class.\n");
		return -1;
	}

	/*register your own device in sysfs. and this will cause udev to create corresponding device node*/
//	device_create(battery_class, NULL, devno, "battery", "%ds",  0); ///////
	device_create(battery_class, NULL, devno, "battery", "battery%d",  0); ///////

	proc_power = proc_mkdir("power", NULL);
        proc_power_status = create_proc_entry("battery_status", 777, proc_power);
	if (proc_power_status)
		proc_power_status->read_proc = proc_read_status;
	
        proc_power_mode = create_proc_entry("battery_mode", 777, proc_power);
	if (proc_power_mode)
		proc_power_mode->read_proc = proc_read_mode;

	init_timer(&timer);
	timer.expires = jiffies + 5 * HZ;
	timer.function = timer_func;
	timer.data = 0;
	add_timer(&timer);

	return 0;
}

static void  demo_module_exit(void)
{
	
	del_timer(&timer);
	cdev_del(&demo_cdev.cdev);
	device_destroy(battery_class, devno);
	class_destroy(battery_class);
	if (devno){
		unregister_chrdev_region(devno, 1);
		cdev_del(&demo_cdev.cdev);
	}
	kfree(demo_cdev.buf);
	

	remove_proc_entry("proc_power_status", proc_power);
	remove_proc_entry("proc_power_mode", proc_power);
	remove_proc_entry("power", NULL);
}

module_init(demo_module_init);
module_exit(demo_module_exit);

MODULE_LICENSE("GPL");
