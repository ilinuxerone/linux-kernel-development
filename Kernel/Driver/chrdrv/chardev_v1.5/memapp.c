#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>             /*mmap() system call included here*/


int main(int argc, char *argv[])
{
	int  fd;
	char  *start;
	char  *buf;
	
	fd = open("/dev/memdev0", O_RDWR);
	if (fd < 0){
		fprintf(stderr, "open /dev/memdev0 failed:%s\n", strerror(errno));
		exit(1);
	}
	
	buf = (char *)malloc(100);
	memset(buf, 0, 100);
	start = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (MAP_FAILED == start){
		fprintf(stderr, "mmap failed:%s\n", strerror(errno));
		return 1;
	}
	
	strcpy(buf, start);
	sleep(1);
	printf("buf 1 = %s\n", buf);
	
	strcpy(start, "buf is NOt null!");
	
	memset(buf, 0, 100);
	strcpy(buf, start);
	sleep(1);
	printf("buf 2:%s\n", buf);
	
	munmap(start, 100);
	free(buf);
	close(fd);
	
	return 0;
}
