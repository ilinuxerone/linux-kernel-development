//快设备驱动的注册于注销

/*块设备初始化函数主要给工作
*1. 分配初始化请求队列，绑定请求队列和请求函数
*2. 分配初始化gendisk， 给gendisk的major ， fops， queue等成员赋值， 最后添加gendisk
*3. 注册快设备驱动
*/
static int __init  xxx_init(void)
{
	
	//块设备驱动注册
	if (register_blkdev(XXX_MAJOR, "xxx")){
		err = -EIO;
		goto out_queue;
	}
	
	//请求队列初始化
	xxx_queue = blk_init_queue(xxx_request, xxx_lock);
	if (!xxx_queue){
		goto out_queue;
	}
	
	//硬件扇区尺寸设置
	blk_queue_hardsect_size(xxx_queue, xxx_blocksize);
	xxx_disks = alloc_disk(minors);
	//gendisk初始化
	xxx_disks->major = XXX_MAJOR;
	xxx_disks->first_minor = 0;
	xxx_disks->fops = &xxx_ops;
	xxx_disks->queue = xxx_queue;
	sprintf(xxx_disks->disk_name, "xxx%d", i);
	set_capacity(xxx_disks, xxx_size * 2);
	add_disk(xxx_disks);  //添加gendisk
	return 0;
out_queue:
	unregister_blkdev(XXX_MAJOR, "xxx");
out: 
	put_disk(xxx_disks);
	blk_cleanup_queue(xxx_queue);
	return -ENOMEM;
}

/*跨设备驱动退出函数主要工作
*1. 清除请求队列。
*2. 删除gendisk和对gendisk的引用。
*3. 删除对块设备的引用， 注销块设备驱动。
*/

static  void __exit   xxx_exit(void)
{
	if (bdev){
		invalidata_bdev(xxx_bdev, 1);
		blkdev_put(xxx_bdev);
	}
	del_gendisk(xxx_disks);
	put_disk(xxx_disks);
	blk_cleanup_queue(xxx_queue);
	unregister_blkdev(XXX_MAJOR, "xxx");
}


/* 块设备的打开与释放
*open函数模板
*/
static int xxx_open(struct inode *inode, struct file *filp)
{
	struct xxx_dev *dev;
	
	dev = inode->i_bdev->bd_disk->private_data;
	filp->private_data = dev;
	......
	return 0;
}

static int xxx_release(struct inode *inode, struct file *filp)
{
	struct xxx_dev  dev;
	dev = inode->i_bdev->bd_disk->private_data;
	......
	return 0;
}

/*块设备的ioctl函数
*实际上在一个现代块设备驱动程序中，许多ioctl命令根本不用实现。
*或只需实现很少部分。
*/
int xxx_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)\
{
	
	
}

/*块设备的IO请求处理
*块设备驱动对块设备进行读写操作，主要通过request来实现。
*块设备驱动请求函数的原型为：
*void request(request_queue_t  *queue);
*/
static void xxx_request(request_queue_t  *q)
{
	struct request *req;
	while (req = elv_next_request(q) != NULL){
		struct xxx_dev *dev = req->rq_diisk->private_data;
		if (!blk_fs_request(req))  //判断是否是文件系统请求
		{
			printk(KERN_NOTICE "skip non_fs request");
			end_request(req, 0);/// 通知请求处理失败
			continue;
		}
	xxx_transfer(dev, req->sector, req->current_nr_sectors, req->buffer, rq_data_dir(req));
	end_request(req, 1);//通知成功完成这个请求
	}
}

//完成具体的块设备操作
static void xxx_transfer(struct xxx_dev *dev, unsigned long sector, unsigned long nsect, char *buffer, int write)
{
	unsigned long offset = sector * KERNEL_SECTOR_SIZE;
	unsigned long nbytes = nsect * KERNEL_SECTOR_SIZE;
	if ((offset + nbytes) > dev->size){
		printk(KERN_NOTICE "Beyond-end write(%ld %ld)\n", offset, nbytes);
		return ;
	}
	
	if (write){
		write_dev(offset, buffer, nbytes);
	} else {
		read_dev(offset, buffer, nbytes);
	}
}
	
	
