#include <linux/module.h>

#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>       /*        */
/*#include <asm/spinlock.h>*/
/*#include <linux/interrupt.h>*/
#include <asm/system.h>

#include "memdev.h"


static int mem_major = MEMDEV_MAJOR;
module_param(mem_major, int, S_IRUGO);

struct mem_dev  *mem_devp;
struct cdev  cdev;


int mem_open(struct inode *inode, struct file *filp)
{
	struct mem_dev  *dev;
	
	int num = MINOR(inode->i_rdev);
	/*int num = iminor(inode)*/
	
	if (num >= MEMDEV_NR_DEVS)
		return -ENODEV;
	dev= &mem_devp[num];
	
	filp->private_data = dev;
	
	return 0;
}

int mem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t mem_read(struct file *filp, char __user *buf, size_t  size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int  ret = 0;
	struct mem_dev *dev = filp->private_data;
	
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
		
	if (p >= MEMDEV_SIZE)
		return 0;
	if  (count > MEMDEV_SIZE - p)
		count = MEMDEV_SIZE - p;
	
	if (copy_to_user(buf, (void *)dev->data + p, count)){
		ret = -EFAULT;
		goto out;
	} else {
		*ppos += count;
		ret = count;
	
		printk(KERN_INFO "read %d bytes from %d\n", count, p);
	}
	out:
		up(&dev->sem);
		return  ret;
	
}

static ssize_t  mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct mem_dev   *dev= filp->private_data;
	
	/*
	ret = down_interruptible(&sem); 
	if(ret){ 
	/* undo whatever change you made 
	return -ERESTARTSYS; 
	} 
	通常情况下，down_interruptible()一般在函数的开头，一般没有做什么实质性的工作，因此直接返回-ERESTARTSYS即可。 
	如果你做了一些工作，在返回-ERESTARTSYS之前，必须undo之。如果无法undo，那你就返回-EINTR。 
	因此说，并不是你来判断是-ERESTARTSYS还是-EINTR，而是你决定返回哪个， 
	能undo就返回-ERESTARTSYS，不能undo，就返回-EINTR。
	*/	
	
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if (p >= MEMDEV_SIZE)
		return 0;
	if (count > MEMDEV_SIZE - p)
		count = MEMDEV_SIZE - p;
	
	if (copy_from_user(dev->data + p, buf, count)){
		ret = -EFAULT;
		goto out;
	} else {
		*ppos += count;
		ret = count;
	}
	
	out:
		up(&dev->sem);
		return ret;
}

static loff_t mem_llseek(struct file *filp, loff_t offset, int whence)
{
	loff_t   newpos;
	
	switch (whence) {
		case 0: 
			newpos = offset;
			break;
		case 1:
			newpos = filp->f_pos + offset;
			break;
		case 2:
			newpos = MEMDEV_SIZE - 1 + offset;
			break;
		default:
			return -EINVAL;
	}
	
	if ((newpos < 0) || (newpos > MEMDEV_SIZE))
		return -EINVAL;
	filp->f_pos = newpos;
	
	return newpos;
}

static struct file_operations mem_ops = {
	.owner = THIS_MODULE,
	.llseek = mem_llseek,
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
};

static int __init memdev_init(void)
{
	int  result = 0;
	int  i;
	
	dev_t devno = MKDEV(mem_major, 0);
	
	if (mem_major){
		result = register_chrdev_region(devno, 2, "memdev");
	}else {
		result = alloc_chrdev_region(&devno, 0, 2, "memdev");
		mem_major = MAJOR(devno);
	}
	if (result < 0){
		return result;
	}
	
	cdev_init(&cdev, &mem_ops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &mem_ops;
	
	cdev_add(&cdev, MKDEV(mem_major, 0), MEMDEV_NR_DEVS);
	
	mem_devp = kmalloc(MEMDEV_NR_DEVS * sizeof(struct mem_dev), GFP_KERNEL);
	if (!mem_devp){
		result = -ENOMEM;
		goto  fail_malloc;
	}
	memset(mem_devp, 0, sizeof(struct mem_dev) * MEMDEV_NR_DEVS);
	
	for (i = 0; i < MEMDEV_NR_DEVS; i++){
		mem_devp[i].size = MEMDEV_SIZE;
		mem_devp[i].data = kmalloc(MEMDEV_SIZE, GFP_KERNEL);
		memset(mem_devp[i].data, 0, MEMDEV_SIZE);
		sema_init(&mem_devp[i].sem, 1);
	}
	
	return result;
	
	fail_malloc:
		unregister_chrdev_region(devno, 2);
		return result;
}

static void __exit memdev_exit(void)
{
	cdev_del(&cdev);
	kfree(mem_devp);     /*漏洞mem_devp[i].data的内存还没有释放*/
	unregister_chrdev_region(MKDEV(mem_major, 0), 2);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhihong");
MODULE_VERSION("v1.1");

module_init(memdev_init);
module_exit(memdev_exit);


