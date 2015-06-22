//���豸�������� ����linux2.6.35
#include <linux/genhd.h>
struct gendisk {
	int  major;
	int  first_minor;
	int  minors;
	
	char disk_name[DISK_NAME_LEN]; /////
	...................
	struct kobject *slave_dir;
	const struct block_device_operations *fops;
	struct request_queue *queue;
	void  *private_data;
	.....................
};

struct gendisk ��һ����̬����Ľṹ������Ҫ�ر���ں˲�������ʼ����
struct gendisk *alloc_disk(int minors);
//minor���������ʹ�õĴα����Ŀ��һ��Ҳ���Ǵ��̷������������˺�minor�����޸�

void del_gendisk(struct gendisk *gd);

put_disk(struct gendisk *gd);
get_disk(struct gendisk *gd);

struct kobject *get_disk(struct gendisk *disk);
void put_disk(struct gendisk *disk);
//ע�����
void add_disk(struct gendisk *gd);
//�ر�ע����ǣ� ��add_disk�����ĵ��ñ�������������ĳ�ʼ������
//��ɲ�����Ӧ���̵�����֮��

//����gendisk����
void set_capacity(struct gendisk *disk, sector_t size);
//���豸����С�Ķ��Ѱַ��Ԫ�������� ����Ĵ�С��512�ֽ�
//�����Ĵ�С���豸���������ԣ� ���������п��豸�Ļ�����Ԫ


//struct block_device_operations 
#include <linux/blkdev.h>
struct block_device_operations {
	int (*open)(struct block_device *, fmode_t);
	int (*release)(struct gendisk *, fmode_t);
	int (*ioctl)(struct block_device *, fmode_t, unsigned, unsigned long);
	..............
	int (*media_changed)(struct gendisk *);
	//���ں˵���������Ƿ�ȡ�����صĽ����Ѿ��ı䣬����ı䷵�ط�0ֵ
	//���������������֧�ֿ��ƶ����ʵ���������
	..........
	struct module *owner;
};

struct bio
//��һ���鱻�����ڴ棬���ڶ�����ȴ�д��ʱ�� ��Ҫ�洢��һ����������
//ÿ����������һ�����Ӧ���൱�ڴ��̿����ڴ��еı�ʾ��
//����������Ϣ��bio�ṹ���ʾ���ýṹ������������ֳ���Ƭ��������ʽ��֯�Ŀ�IO������
//һ��Ƭ����һ��С���������ڴ滺����������Ҫ��֤����������һ��Ҫ������
//�����segmentֻ�Ǵ������ݵĵ�λ�������ǲ���ϵͳ�ж�ҳʽ�����ڴ���Ǹ��εĸ��

#include <linux/bio.h>
struct bio {
	sector_t   bi_sector;   
	struct bio *bi_next;
	struct 	block_device *bi_bdev;
	unsigned long bi_flags;
	unsigned long bi_rw;
	
	unsigned short bi_vcnt;
	unsigned short bi_idx;
	struct bio_vec *bi_io_vec;
	...................
};

//struct bio_vec��������һ���ض���Ƭ�Σ�Ƭ�����ڵ�����ҳ
//��������ҳ�е�ƫ��λ�ã��ͳ��ȡ�
#include <linux/bio.h>
struct bio_vec {
	struct page *bv_page;
	unsigned int bv_len;
	unsigned int bv_offset;
};

//ÿһ����IO����ͨ��bio�����ʾ
/*
�������
���豸������Ŀ����󱣴�����������У��ö�����request_queue�ṹ���ʾ��������
<linux/blkdev.h>�У�����һ��˫����������Լ���ؿ�����Ϣ��
ͨ���ں������ļ�ϵͳ�����߲�Ĵ��뽫������뵽��������У�
ֻҪ������в�Ϊ�գ����ж�Ӧ�Ŀ��豸��������ͻ�Ӷ�ͷ
��ȡ����Ȼ������뵽��Ӧ�Ŀ��豸��ȥ����������е�ÿһ���һ��
������������request�ṹ���ʾ��
request_queue��������У�ͨ�����ҵ�request������Щ��������һ�壬Ȼ����
request�а���bio��Ȼ��ͨ��bio�ṹ���ҵ���Ӧ��page��Ȼ��ͨ��page��ȡ�����ڴ��е���Ϣ��

*/

#include <linux/blkdev.h>
struct request_queue {
	struct list_head  queue_head;
	struct request  *last_merge;
	struct elevator_queue  *elevator;
	
	struct request_list rq;
	
	request_fn_proc  *request_fn;  //important
	make_request_fn  *make_request_fn;
	
	.................
	struct kobject  kobj;
	spinlock_t  *queue_lock;
	.............
};

#include <linux/blkdev.h>
struct request {
	struct list_head  queuelist;
	struct call_single_data csd;
	
	struct  request_queue  *q; ///
	sector_t  sector;
		
	struct bio *bio;
	struct bio *biotail;
	
	char *buffer;  /*kaddr of the current segment if available*/
	
};

/*���豸������д
*/	
//�豸ע��
#include <linux/fs.h>
int register_blkdev(unsigned int major, const char *name);
����majorΪ0�� �ں˷���һ���µ����豸�Ų����ظ������ߣ�ʧ�ܷ���һ����ֵ��
ע��ɹ�����/proc/devices����ʾ����

int unregister_blkdev(unsigned int major, const char *name);


//������в���
#include <linux/blkdev.h>
struct request_queue *blk_init_queue(request_fn_proc *, spinlock_t *);

void blk_cleanup_queue(struct request_queue *);

//����ĺ������ڲ�ʹ��������е������
struct request_queue *blk_alloc_queue(gfp_t);
void blk_queue_make_request(struct request_queue *, make_request_fn *);
typedef int (make_request_fn)(struct request_queue *q, struct bio *bio);

 void blk_start_queue(struct request_queue *q);
 void blk_stop_queue(struct request_queue *qs);

void blk_queue_logical_block_size(struct request_queue *, unsigned short);
void blk_queue_physical_block_size(struct request_queue *, unsigned short);
struct request *blk_fetch_request(struct request_queue *q);
bool blk_end_request(struct request *rq, int err, unsigned int nr_bytes);
bool __blk_end_request_all(struct request *rq, int error);
bool __blk_end_request_cur(struct request *rq, int error);
errro: o for success, < 0 for error;
rq: the request being processed
nr_bytes : number of bytes to complete.

#define blk_fs_request(rq);  ((rq)->cmd_type == REQ_TYPE_FS);

/*ʵ��������*/
//���ݽṹ
struct sbull_dev {
	int	size;     /*Device size in sectors*/
	u8	*data;	 /*The data array*/
	short	users;   /*How many users*/
	short	media_change;
	spinlock_t lock;  /*For mutual exclusion*/
	struct  request_queue *queue; /*The device request queue*/ gendisk�в��������������������ﻹҪ�أ�����
	struct  gendisk *gd;      /*The gendisk structure*/
	struct timer_list timer;  /*For simulated media changes*/
};

/*������ṹ�У� struct request_queue �� struct gendisk 
������ṹ����Ҫ��Ա��Ҳ�ǿ��豸�е���Ҫ�ṹ*/

//��ʼ������
step 1: ע��
register_blkdev(sbull_major, "sbull");
��ע����豸����һ�������豸�ţ�Ϊ0��ʾ��̬����

step 2�� ��������豸��Ķ���ʵ��
Device = kmalloc(ndevices * sizeof(struct sbull_dev), GFP_KERNEL);
//����������豸�ĺ������ݽṹ������ndevice��������豸����ʵ��
step 3�� ��ʼ��ʵ��
setup_device(Devices + i, i);
��ʼ��ʵ�壬��������ӵ�block����ȥ������������Ҫ
���������һЩ������
->��ʼ��һ��������
spin_lock_init(&dev->lock);
->����һ��������У�������һ���������������ƶ��еķ���
dev->queue = blk_init_queue(sbull_full_request, &dev->lock);
->���䣬��ʼ������װ��Ӧ��gendisk�ṹ
dev->gd = alloc_disk(SBULL_MINORS);
if (!dev->gd) {
	printk(KERN_NOTICE "alloc_disk failure!\n");
	goto out_vfree;
}

dev->gd->major = sbull_major;
dev->gd->first_minor = which * SBULL_MINORS;
dev->gd->fops = &sbull_ops;
dev->gd->queue = dev->queue;
dev->gd->private_data = dev;
snprintf(dev->gd->disk_name, 32, "sbull%c", which + 'a');
set_capacity(dev->gd, nsectors * (hardsect_size/KERNRL_SECTOR_SIZE));

//���add_disk()���������ʼ�����̣���һ��һ��Ҫ�ڳ�ʼ��������ڵ��ã���Ϊ
add_disk()�󣬿��ܾͻ���ô��̵Ĳ��������� �����ʼ����û��ɾͻ����

//���豸����struct block_device_operations �ṹ
sbullģ���е�struct block_device_operations�ṹ


static struct block_device_opetations sbull_ops = {
	.owner = THIS_MODULE,
	.open = sbull_open,
	.release = sbull_release,
	.media_changed = sbull_media_changed,
	.revalidate_disk = sbull_revalidate,
	.ioctl = sbull_ioctl
};

open and release�����������Ĺ��ܾ��������û������ͼ��ټ���
media_changed ��revalidate_disk���ǶԿ��ƶ����ʵ�֧�֣���U������
���弴�õ��豸�Ϳ�ʵ�������������� media_changed�Ǽ������Ƿ�ı䣬
�ı伴���ط�0��revalidata_disk�����ʸı��ִ�С�����֮�������ϵ���ǲ��ù��ģ�
��Ҫʵ�����������ʵ�弴�ɡ�

ioctl�����Ĺ���Ҳ���ˣ�ʵ�ʵĴ����豸���Ҳ��Ҫʵ�ֶԴ�����Ϣ�Ĳ�ѯ��

//������
���豸��������ĺ������������֡���Ƶĺû�ֱ��Ӱ������ܡ�
 dev->queue = blk_init_queue(sbull_full_request, &dev->lock);
 ����������ǰ����ɵ��������dev->queue��������sbull_full_request����һ��
 
 static void sbull_full_request(struct request_queue *q)
 {
 	int nsect;
 	struct request *req;
 	struct sbull_dev *dev;
 	
 	//req = blk_fetch_request(q);
 	//req = elv_next_request(q); old version
 	dev = req->rq_disk->private_data;
 	while ((req = blk_fetch_request(q)) != NULL){
 		if (!blk_fs_request(req)){
 			printk(KERN_NOTICE "Skip non-fs request\n");
 			__blk_end_request_all(req, -EIO);
 			continue;
 		}
 		
 		nsect = sbull_xfer_request(dev, req);
 		__blk_end_request(req, 0, (nsect<<9));
 		//req = blk_fetch_request(q);
 	}
 }
 
 req = blk_fecth_request(q)��ö�����һ��δ��ɵ�����
 ����������ͣ���������ļ�ϵͳ�����������������
  sbull_xfer_request��������ʵ�ʵ����ݴ��䣬ֻ�и��������ʱ���Ż�
  �õ���һ������
 
 //���豸����������
 ����ҳ���棨cache����linux�ں�ʵ�ֵ�һ����Ҫ���̻��档
 ����Ҫ���ٶԴ��̵�IO����������Ľ�����ͨ���ɴ����е�����
 ���浽�����ڴ��У��ѶԴ��̵ķ��ʱ�Ϊ�������ڴ�ķ��ʡ�
 
 ҳ���ٻ�������RAM�е�����ҳ��ɵģ� ������ÿһҳ����Ӧ�Ŵ����еĶ���顣
 ÿ���ں˿�ʼִ��һ��ҳIO����ʱ�����Ȼ�����Ҫ�������Ƿ��ڸ��ٻ����У�
 ����ڣ���ô�ں˾�ֱ��ʹ�ø��ٻ����е����ݣ��Ӷ�������ʴ��̡�
 
 ���ٻ����е����ݺʹ����ϵ�������֯��ʽ�ǲ�ͬ�ģ�linux�ں�ͨ��
 buffer_head�ṹ������ٻ��档buffer_head�ṹ�������һ������������������
 �����е�һ���鵽ҳ���ӳ�䡣
 #include <linux/buffer_head.h>
 struct buffer_head {
 	unsigned long  b_state;
 	struct buffer_head  *b_this_page;
 	struct page *b_page;
 	
 	sector_t  b_blocknr;
 	size_t  b_size;
 	char *b_data;
 	.............
 	atomic_t  b_count;
 	void *b_private;
 	......
 };
 
 IO������
 IO���������һ�����ӵ����ݽṹ���ں˵����ط���Ҫ���ʸýṹ����������ɾ���
 ����Ҫ������Ӧ��ʩ���������õ���������Ӧ�������̳�������ʱ�䡣
 
 ��Ⱥ����
 ��Ⱥ�ǽ��������������ݿ�Ĳ�������ϲ�������һ�ַ�����
 ��Ⱥ�ܴ������������ô����ܼ������ݴ��䣬ͨ������������������ṹ��
 ���Խ�ʡ�ں����ڴ��ʹ�á�
 
 �����
 �ں�Ĭ��Ϊÿ�����豸��ά��һ��������IO������У�������Щ����£��������в�����
 ���ŵġ����ж�����̵�ϵͳ�У�ÿ�������ܶ���������������������ܲ��в����������
 ���ܣ������ڵ������е����������޷�ʵ����һ���ԡ�
 
 
 	
 