
#ifndef  __MEMDEV_H
#define  __MEMDEV_H

#ifndef  MEMDEV_MAJOR
#define  MEMDEV_MAJOR  255
#endif

#ifndef  MEMDEV_NR_DEVS
#define  MEMDEV_NR_DEVS  2
#endif

#ifndef  MEMDEV_SIZE
#define  MEMDEV_SIZE  4096
#endif

struct mem_dev
{
	char  *data;
	unsigned long  size;
//	struct semaphore sem;
	wait_queue_head_t  inq;
};



#endif /*MEMDEV_H*/
