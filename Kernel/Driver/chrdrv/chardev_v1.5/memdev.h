#ifndef   __MEMDEV_H
#define   __MEMDEV_H

#ifndef   MEMDEV_MAJOR
#define   MEMDEV_MAJOR   255
#endif

#ifndef   MEMDEV_NR_DEVS  
#define   MEMDEV_NR_DEVS  2
#endif

#ifndef   MEMDEV_SIZE
#define   MEMDEV_SIZE   4096
#endif

struct mem_dev
{
	unsigned long  size;
	char           *data;
	
};

#define   MEMDEV_IOC_MAGIC  'K'

#define  MEMDEV_IOCPRINT  	_IO(MEMDEV_IOC_MAGIC, 1)
#define  MEMDEV_IOCGETDATA 	_IOR(MEMDEV_IOC_MAGIC, 2, int)
#define  MEMDEV_IOCSETDATA 	_IOW(MEMDEV_IOC_MAGIC, 3, int)

#define  MEMDEV_IOC_MAXNR  3

#endif /*__MEMDEV_H*/