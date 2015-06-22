#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <asm/system.h>
#include <asm/io.h>
/*#include <asm/irq.h>*/
/*#include <linux/interrupt.h>*/
/*#include <linux/spinlock.h>*/
/*#include <linux/semaphore.h>*/
/*#include <linux/ioctl.h>*/

#include <linux/poll.h>
#include "memdev.h"

static int mem_major = MEMDEV_MAJOR;
bool  have_data = false;

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
	dev = &mem_devp[num];
	
	filp->private_data = dev;
	
	return 0;
}

int mem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *offset)
{
	unsigned long  p = *offset;
	unsigned int count = size;
	int ret = 0;
	struct mem_dev  *dev = filp->private_data;
	
	if (p >= MEMDEV_SIZE)
		return 0;
	if (count > MEMDEV_SIZE - p)
		count = MEMDEV_SIZE - p;
		
	while (!have_data) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		
		wait_event_interruptible(dev->inq, have_data);
	}
	
	if (copy_to_user(buf, (void *)(dev->data + p), count)) {
		ret = -EFAULT;
	} else {
		*offset += count;
		ret = count;
         	printk(KERN_INFO "read %d bytes(s) from %d\n", count, p);
	}
	
	have_data = false;
	
	return ret;
}

ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *offset)
{
	unsigned long p = *offset;
	unsigned int count = size;
	int ret = 0;
	struct mem_dev *dev = filp->private_data;
	
	if (p >= MEMDEV_SIZE)
		return 0;
	if (count > MEMDEV_SIZE - p)
		count = MEMDEV_SIZE - p;
		
	if (copy_from_user(dev->data, buf, count))
		ret = -EFAULT;
	else {
		*offset += count;
		ret = count;
	}
	
	have_data = true;
	
	wake_up(&(dev->inq));
	
	return ret;	
}	

loff_t  mem_llseek(struct file *filp, loff_t offset, int whence)
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
		
		if ( (newpos < 0) || (newpos > MEMDEV_SIZE) )
			return -EINVAL;
			
		filp->f_pos = newpos;
		
		return newpos;
}

unsigned int mem_poll(struct file *filp, poll_table *wait)
{
	struct mem_dev  *dev = filp->private_data;
	unsigned int mask = 0;
	
	poll_wait(filp, &dev->inq, wait);
	
	if (have_data)  
		mask |= POLLIN  | POLLRDNORM;
	
	return mask;
}

int mem_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
{
	int  err = 0;
	int  ret = 0;
	int  ioarg = 0;
	
	if (_IOC_TYPE(cmd) != MEMDEV_IOC_MAGIC)
		return -EINVAL;
	if (_IOC_NR(cmd) > MEMDEV_IOC_MAXNR)
		return -EINVAL;
		
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
		
	if (err)
		return -EFAULT;
	
	switch (cmd){
		case MEMDEV_IOCPRINT:
			printk("<--CMD MEMDEV_IOCPRINT Done->\n");
			break;
		case MEMDEV_IOCGETDATA:
			ioarg = 1101;
			ret = __put_user(ioarg, (int *)arg);
			break;
		case MEMDEV_IOCSETDATA:
			ret = __get_user(ioarg, (int *)arg);
			printk("<-- In Kernel MEMDEV_IOCSETDATA ioarg = %d-->\n\n", ioarg);
			break;
		default:
			return -EINVAL;
	}
	
	return ret;	
}

static int mem_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct mem_dev  *dev = filp->private_data;
	
	vma->vm_flags |=  VM_IO;
	vma->vm_flags |= VM_RESERVED;
	
	if (remap_pfn_range(vma, vma->vm_start, virt_to_phys(dev->data)>>PAGE_SHIFT, vma->vm_end - vma->vm_start, vma->vm_page_prot))
		return -EAGAIN;
		
	return 0;			
}

static struct file_operations  mem_ops = 
{
	.owner = THIS_MODULE,
	.llseek = mem_llseek,
	.open = mem_open,
	.release = mem_release,
	.read = mem_read,
	.write = mem_write,
	.poll = mem_poll,
	.ioctl = mem_ioctl,
	.mmap = mem_mmap,
};

static int __init memdev_init(void)
{
	int  result = 0;
	int  i;
	
	dev_t  devno = MKDEV(mem_major, 0);
	if (mem_major){
		result = register_chrdev_region(devno, 2, "memdev");
	} else {
		result = alloc_chrdev_region(&devno, 0, 2, "memdev");
		mem_major = MAJOR(devno);
	}
	
	if (result < 0)
		return result;
	
	cdev_init(&cdev, &mem_ops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &mem_ops;
	
	cdev_add(&cdev, MKDEV(mem_major, 0), MEMDEV_NR_DEVS);
	
	mem_devp = kmalloc(MEMDEV_NR_DEVS * sizeof(struct mem_dev), GFP_KERNEL);
	if (!mem_devp) {
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(mem_devp, 0, sizeof(mem_devp) * MEMDEV_NR_DEVS);
	
	for (i = 0; i < MEMDEV_NR_DEVS; i++) {
		mem_devp[i].size = MEMDEV_SIZE;
		mem_devp[i].data = kmalloc(MEMDEV_SIZE, GFP_KERNEL);
		memset(mem_devp[i].data, 0, MEMDEV_SIZE);
		
		init_waitqueue_head(&(mem_devp[i].inq));
	}
	
	return result;
	
	fail_malloc:
		unregister_chrdev_region(devno, 2);
		return result;
}

static void __exit memdev_exit(void)
{
	cdev_del(&cdev);
	kfree(mem_devp);
	unregister_chrdev_region(MKDEV(mem_major, 0), 2);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhihong");
MODULE_VERSION("v1.4");

module_init(memdev_init);
module_exit(memdev_exit);
