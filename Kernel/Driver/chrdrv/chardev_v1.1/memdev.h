
#ifndef   __MEMDEV_H_
#define	  __MEMDEV_H_

#ifndef  MEMDEV_MAJOR
#define  MEMDEV_MAJOR  255
#endif

#ifndef  MEMDEV_NR_DEVS
#define  MEMDEV_NR_DEVS   2
#endif

#ifndef  MEMDEV_SIZE
#define  MEMDEV_SIZE   4096
#endif

struct mem_dev
{
	char *data;
	unsigned  long size;
	struct semaphore sem;
};       /*后面的分号一定不能忘记啦*/

#endif   /*__MEMDEV_H*/