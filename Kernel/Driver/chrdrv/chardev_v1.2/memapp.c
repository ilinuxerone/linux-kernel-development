#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "memdev.h"

int main(int argc, char *argv[])
{
	int fd = 0;
	int cmd;
	int arg = 0;
	char buf[4096];
	
	fd = open("/dev/memdev0", O_RDWR);
	if (fd < 0){
		fprintf(stderr, "Open dev mem0 error!\n");
		return -1;
	}
	
	printf("<----call MEMDEV_IOCPRINT--->\n");
	cmd = MEMDEV_IOCPRINT;
	if (ioctl(fd, cmd, &arg) < 0){
		fprintf(stderr, "Call cmd MEMDEV_IOCPRINT fail!\n");
		return -1;
	}
	
	printf("<---Call MEMDEV_IOCSETDATA---\n");
	cmd = MEMDEV_IOCSETDATA;
	arg = 2012;
	if (ioctl(fd, cmd, &arg) < 0){
		fprintf(stderr, "Call cmd MEMDEV_IOCSETDATA fail\n");
		return -1;
	}
	
	printf("<---Call MEMDEV_IOCGETDATA --->\n");
	cmd = MEMDEV_IOCGETDATA;
	if (ioctl(fd, cmd, &arg) < 0) {
		fprintf(stderr, "<---call cmd MEMDEV_IOCGETDATA failed--->\n");
		return -1;
	}
	printf("<---In User Space MEMDEV__IOCGETDATA get data is %d\n", arg);
	
	close(fd);
	return 0;
	
	
}
		
