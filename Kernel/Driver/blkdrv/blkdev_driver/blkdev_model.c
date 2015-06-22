//���豸������ע����ע��

/*���豸��ʼ��������Ҫ������
*1. �����ʼ��������У���������к�������
*2. �����ʼ��gendisk�� ��gendisk��major �� fops�� queue�ȳ�Ա��ֵ�� ������gendisk
*3. ע����豸����
*/
static int __init  xxx_init(void)
{
	
	//���豸����ע��
	if (register_blkdev(XXX_MAJOR, "xxx")){
		err = -EIO;
		goto out_queue;
	}
	
	//������г�ʼ��
	xxx_queue = blk_init_queue(xxx_request, xxx_lock);
	if (!xxx_queue){
		goto out_queue;
	}
	
	//Ӳ�������ߴ�����
	blk_queue_hardsect_size(xxx_queue, xxx_blocksize);
	xxx_disks = alloc_disk(minors);
	//gendisk��ʼ��
	xxx_disks->major = XXX_MAJOR;
	xxx_disks->first_minor = 0;
	xxx_disks->fops = &xxx_ops;
	xxx_disks->queue = xxx_queue;
	sprintf(xxx_disks->disk_name, "xxx%d", i);
	set_capacity(xxx_disks, xxx_size * 2);
	add_disk(xxx_disks);  //���gendisk
	return 0;
out_queue:
	unregister_blkdev(XXX_MAJOR, "xxx");
out: 
	put_disk(xxx_disks);
	blk_cleanup_queue(xxx_queue);
	return -ENOMEM;
}

/*���豸�����˳�������Ҫ����
*1. ���������С�
*2. ɾ��gendisk�Ͷ�gendisk�����á�
*3. ɾ���Կ��豸�����ã� ע�����豸������
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


/* ���豸�Ĵ����ͷ�
*open����ģ��
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

/*���豸��ioctl����
*ʵ������һ���ִ����豸���������У����ioctl�����������ʵ�֡�
*��ֻ��ʵ�ֺ��ٲ��֡�
*/
int xxx_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)\
{
	
	
}

/*���豸��IO������
*���豸�����Կ��豸���ж�д��������Ҫͨ��request��ʵ�֡�
*���豸������������ԭ��Ϊ��
*void request(request_queue_t  *queue);
*/
static void xxx_request(request_queue_t  *q)
{
	struct request *req;
	while (req = elv_next_request(q) != NULL){
		struct xxx_dev *dev = req->rq_diisk->private_data;
		if (!blk_fs_request(req))  //�ж��Ƿ����ļ�ϵͳ����
		{
			printk(KERN_NOTICE "skip non_fs request");
			end_request(req, 0);/// ֪ͨ������ʧ��
			continue;
		}
	xxx_transfer(dev, req->sector, req->current_nr_sectors, req->buffer, rq_data_dir(req));
	end_request(req, 1);//֪ͨ�ɹ�����������
	}
}

//��ɾ���Ŀ��豸����
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
	
	
