//块设备驱动程序， 基于linux2.6.35
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

struct gendisk 是一个动态分配的结构，它需要特别的内核操作来初始化。
struct gendisk *alloc_disk(int minors);
//minor是这个磁盘使用的次编号数目，一般也就是磁盘分区的数量，此后minor不能修改

void del_gendisk(struct gendisk *gd);

put_disk(struct gendisk *gd);
get_disk(struct gendisk *gd);

struct kobject *get_disk(struct gendisk *disk);
void put_disk(struct gendisk *disk);
//注册磁盘
void add_disk(struct gendisk *gd);
//特别注意的是， 对add_disk（）的调用必须在驱动程序的初始化工作
//完成并能响应磁盘的请求之后

//设置gendisk容量
void set_capacity(struct gendisk *disk, sector_t size);
//块设备中最小的额可寻址单元是扇区， 最常见的大小事512字节
//扇区的大小事设备的物理属性， 扇区是所有块设备的基本单元


//struct block_device_operations 
#include <linux/blkdev.h>
struct block_device_operations {
	int (*open)(struct block_device *, fmode_t);
	int (*release)(struct gendisk *, fmode_t);
	int (*ioctl)(struct block_device *, fmode_t, unsigned, unsigned long);
	..............
	int (*media_changed)(struct gendisk *);
	//被内核调用来检查是否取得器重的介质已经改变，如果改变返回非0值
	//这个函数仅适用于支持可移动介质的驱动器。
	..........
	struct module *owner;
};

struct bio
//当一个块被调入内存，即在读入后或等待写出时， 它要存储在一个缓冲区中
//每个缓冲区与一个块对应，相当于磁盘块在内存中的表示。
//缓冲区的信息由bio结构体表示，该结构体代表了正在现场以片段链表形式组织的块IO操作。
//一个片段是一个小块连续的内存缓冲区，不需要保证单个缓冲区一定要连续。
//这里的segment只是处理数据的单位，并不是操作系统中段页式管理内存的那个段的概念。

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

//struct bio_vec描述的是一个特定的片段：片段所在的物理页
//块在物理页中的偏移位置，和长度。
#include <linux/bio.h>
struct bio_vec {
	struct page *bv_page;
	unsigned int bv_len;
	unsigned int bv_offset;
};

//每一个块IO请求都通过bio链表表示
/*
请求队列
块设备将挂起的快请求保存在请求队列中，该队列由request_queue结构体表示，定义在
<linux/blkdev.h>中，包含一个双向请求队列以及相关控制信息。
通过内核中像文件系统这样高层的代码将请求加入到请求队列中，
只要请求队列不为空，队列对应的块设备驱动程序就会从对头
获取请求，然后将其加入到对应的块设备中去，请求队列中的每一项都是一个
单独的请求，由request结构体表示。
request_queue是请求队列，通过它找到request，将这些请求连成一体，然后在
request中包含bio，然后通过bio结构体找到对应的page，然后通过page读取物理内存中的信息。

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

/*块设备驱动编写
*/	
//设备注册
#include <linux/fs.h>
int register_blkdev(unsigned int major, const char *name);
如若major为0， 内核分配一个新的主设备号并返回给调用者，失败返回一个负值。
注册成功后再/proc/devices中显示它。

int unregister_blkdev(unsigned int major, const char *name);


//请求队列操作
#include <linux/blkdev.h>
struct request_queue *blk_init_queue(request_fn_proc *, spinlock_t *);

void blk_cleanup_queue(struct request_queue *);

//下面的函数用于不使用请求队列的情况。
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

/*实验代码分析*/
//数据结构
struct sbull_dev {
	int	size;     /*Device size in sectors*/
	u8	*data;	 /*The data array*/
	short	users;   /*How many users*/
	short	media_change;
	spinlock_t lock;  /*For mutual exclusion*/
	struct  request_queue *queue; /*The device request queue*/ gendisk中不是有请求队列吗，这里干嘛还要呢？？？
	struct  gendisk *gd;      /*The gendisk structure*/
	struct timer_list timer;  /*For simulated media changes*/
};

/*在这个结构中， struct request_queue 与 struct gendisk 
是这个结构的重要成员，也是块设备中的重要结构*/

//初始化流程
step 1: 注册
register_blkdev(sbull_major, "sbull");
先注册块设备，第一个参数设备号，为0表示动态分配

step 2： 创建这个设备快的对象实体
Device = kmalloc(ndevices * sizeof(struct sbull_dev), GFP_KERNEL);
//创建这个块设备的核心数据结构，创建ndevice个这个块设备对象实体
step 3： 初始化实体
setup_device(Devices + i, i);
初始化实体，并把它添加到block层中去。这个步骤很重要
它完成以下一些操作：
->初始化一个自旋锁
spin_lock_init(&dev->lock);
->分配一个请求队列，并用上一步的自旋锁来控制队列的方向
dev->queue = blk_init_queue(sbull_full_request, &dev->lock);
->分配，初始化即安装相应的gendisk结构
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

//最后add_disk()完成整个初始化过程，这一步一定要在初始化的最后在调用，因为
add_disk()后，可能就会调用磁盘的操作函数， 如果初始化还没完成就会出错。

//块设备操作struct block_device_operations 结构
sbull模块中的struct block_device_operations结构


static struct block_device_opetations sbull_ops = {
	.owner = THIS_MODULE,
	.open = sbull_open,
	.release = sbull_release,
	.media_changed = sbull_media_changed,
	.revalidate_disk = sbull_revalidate,
	.ioctl = sbull_ioctl
};

open and release这两个函数的功能就是增加用户计数和减少计数
media_changed 和revalidate_disk就是对可移动介质的支持，像U盘这种
即插即用的设备就可实现这两个函数。 media_changed是检查介质是否改变，
改变即返回非0，revalidata_disk即介质改变后执行。它们之间如何联系我们不用关心，
主要实现这个函数的实体即可。

ioctl函数的功能也简化了，实际的磁盘设备大多也主要实现对磁盘信息的查询。

//请求处理
块设备驱动程序的核心是请求处理部分。设计的好坏直接影响的性能。
 dev->queue = blk_init_queue(sbull_full_request, &dev->lock);
 这个操作就是把生成的请求队列dev->queue与请求函数sbull_full_request绑定在一起。
 
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
 
 req = blk_fecth_request(q)获得队列中一个未完成的请求。
 检查请求类型，如果不是文件系统请求，则结束所有请求。
  sbull_xfer_request在这里是实际的数据传输，只有该请求结束时，才会
  得到下一个请求。
 
 //块设备的其他问题
 高速页缓存（cache）是linux内核实现的一种主要磁盘缓存。
 它主要减少对磁盘的IO操作。具体的讲，是通过吧磁盘中的数据
 缓存到物理内存中，把对磁盘的访问变为对物理内存的访问。
 
 页高速缓存是由RAM中的物理页组成的， 缓存中每一页都对应着磁盘中的多个块。
 每当内核开始执行一个页IO操作时，首先会检查需要的数据是否在高速缓存中，
 如果在，那么内核就直接使用高速缓存中的数据，从而避免访问磁盘。
 
 高速缓存中的内容和磁盘上的数据组织形式是不同的，linux内核通过
 buffer_head结构管理高速缓存。buffer_head结构代表的是一个缓存区，描述的是
 磁盘中的一个块到页面的映射。
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
 
 IO请求锁
 IO请求队列是一个复杂的数据结构，内核的许多地方都要访问该结构，往往会造成竞争
 所以要采用相应措施，而且良好的驱动程序应尽量缩短持有锁的时间。
 
 集群请求
 集群是将磁盘上相邻数据块的操作请求合并起来的一种方法。
 集群能带给我们两个好处，能加速数据传输，通过避免分配冗余的请求结构，
 可以节省内核中内存的使用。
 
 多队列
 内核默认为每个主设备号维护一个单独的IO请求队列，但是有些情况下，单个队列并不是
 最优的。在有多个磁盘的系统中，每个磁盘能独立操作，驱动程序如果能并行操作可以提高
 性能，而基于单个队列的驱动程序无法实现这一特性。
 
 
 	
 