/*linux kernel version 2.6.32.20*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/bio.h>
#include <linux/buffer_head.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>           /*HDIO_GETGEO*/
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>            /*O_ACCMODE*/


static int  sbull_major = 0;
module_param(sbull_major, int, 0);
static int hardsect_size = 512;
module_param(hardsect_size, int, 0);
static int nsectors = 1024;     /*how big the dirve is*/
module_param(nsectors, int, 0);
static int ndevices = 4;
module_param(ndevices, int, 0);

#define SBULL_MINORS   16
#define MINOR_SHIFT	4
#define DEVNUM(kdevnum)  (MINOR(kdev_t_to_nr(kdevnum)) >> MINOR_SHIFT)

#define KERNEL_SECTOR_SIZE  512


/*The representation of our device*/
struct sbull_dev {
	int	size;
	u8	*data;
	short	users;
	spinlock_t  lock;
	struct request_queue *queue;
	struct gendisk *gd;
};

static struct sbull_dev  *Devices = NULL;

static int sbull_open(struct block_device *device, fmode_t  mode)
{
	struct  sbull_dev  *dev = device->bd_disk->private_data;
	
	spin_lock(&dev->lock);
	dev->users++;
	spin_unlock(&dev->lock);
	
	return 0;
}

static int sbull_release(struct gendisk *disk, fmode_t mode)
{
	struct sbull_dev *dev = disk->private_data;
	
	spin_lock(&dev->lock);
	dev->users--;
	spin_unlock(&dev->lock);
	
	return 0;	
}



static struct block_device_operations sbull_fops = {
	.owner = THIS_MODULE,
	.open = sbull_open,
	.release = sbull_release
};

/*
* Handle an I/O request, in sectors.
*/
static void sbull_transfer(struct sbull_dev *dev, unsigned long sector,
				unsigned long nsect, char *buffer, int write)
{
	unsigned long offset = sector*KERNEL_SECTOR_SIZE;
	unsigned long nbytes = nsect*KERNEL_SECTOR_SIZE;
	if ((offset + nbytes) > dev->size) {
		printk (KERN_NOTICE "Beyond-end write (%ld %ld)\n", offset, nbytes);
	return;
	}
	if (write)
		memcpy(dev->data + offset, buffer, nbytes);
	else
		memcpy(buffer, dev->data + offset, nbytes);
}
/*
* The simple form of the request function.
*/
static void sbull_request(struct request_queue *q)
{
	struct request *req;

	req = blk_fetch_request(q);
	while (req != NULL) {
		struct sbull_dev *dev = req->rq_disk->private_data;
		if (! blk_fs_request(req)) {
			printk (KERN_NOTICE "Skip non-fs request\n");
			__blk_end_request_all(req, -EIO);
			continue;
		}
// printk (KERN_NOTICE "Req dev %d dir %ld sec %ld, nr %d f %lx\n",
// dev - Devices, rq_data_dir(req),
// req->sector, req->current_nr_sectors,
// req->flags);
		sbull_transfer(dev, blk_rq_pos(req), blk_rq_cur_sectors(req), req->buffer, rq_data_dir(req));
/* end_request(req, 1); */
		if(!__blk_end_request_cur(req, 0)) {
		req = blk_fetch_request(q);
		}
	}
}
	

/*
* Set up our internal device.
*/
static void setup_devices(struct sbull_dev *dev, int index)
{
	/*
	* Get some memory.
	*/
	memset (dev, 0, sizeof (struct sbull_dev));
	dev->size = nsectors * hardsect_size;
	dev->data = vmalloc(dev->size);
	if (dev->data == NULL) {
		printk (KERN_NOTICE "vmalloc failure.\n");
		return;
	}
	spin_lock_init(&dev->lock);

	/*
	* The timer which "invalidates" the device.
	*/
	dev->queue = blk_init_queue(sbull_request, &dev->lock);
	if (dev->queue == NULL)
		goto out_vfree;

	blk_queue_logical_block_size(dev->queue, hardsect_size);
	dev->queue->queuedata = dev;
	/*
	* And the gendisk structure.
	*/
	dev->gd = alloc_disk(SBULL_MINORS);
	if (! dev->gd) {
		printk (KERN_NOTICE "alloc_disk failure\n");
		goto out_vfree;
	}
	dev->gd->major = sbull_major;
	dev->gd->first_minor = index * SBULL_MINORS;
	dev->gd->fops = &sbull_fops;
	dev->gd->queue = dev->queue;
	dev->gd->private_data = dev;
	snprintf (dev->gd->disk_name, 32, "sbull%c", index + 'a');
	set_capacity(dev->gd, nsectors*(hardsect_size/KERNEL_SECTOR_SIZE));
	add_disk(dev->gd);
	return;
out_vfree:
	if (dev->data)
	vfree(dev->data);
}

static int __init sbull_init(void)
{
	int  i;
	
	/*Get registered.*/
	sbull_major = register_blkdev(sbull_major, "sbull");
	if (sbull_major <= 0){
		printk(KERN_WARNING "sbull: unable to get major number\n");
		return -EBUSY;
	}
	
	/*Allocate the device array, and initialize each one.*/
	Devices = kmalloc(ndevices * sizeof(struct sbull_dev), GFP_KERNEL);
	if (NULL == Devices){
		goto out_unregister;
	}
	for (i = 0; i < ndevices; i++){
		setup_devices(Devices + i, i);
	}
			
	return 0;
out_unregister:
	unregister_blkdev(sbull_major, "sbull");
	return -ENOMEM;
}

static void sbull_exit(void)
{
	int  i;
	
	for (i = 0; i < ndevices; i++){
		struct sbull_dev  *dev = Devices + i;
		
		if (NULL != dev->gd){
			del_gendisk(dev->gd);
			put_disk(dev->gd);
		}
		if (NULL != dev->data){
			vfree(dev->data);
		}
		if (NULL != dev->queue){
			blk_cleanup_queue(dev->queue);
		}
	}
	
	unregister_blkdev(sbull_major, "sbull");
	kfree(Devices);
}

module_init(sbull_init);
module_exit(sbull_exit);