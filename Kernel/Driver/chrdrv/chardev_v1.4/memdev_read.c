#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	int fd;
	fd_set rds;
	int  ret;
	char buf[128];
	
	strcpy(buf, "memdev is char dev!");
	printf("buf is :%s\n", buf);
	
	fd = open("/dev/memdev0", O_RDWR);
	
	FD_ZERO(&rds);
	FD_SET(fd, &rds);
	
	strcpy(buf, "buf is NULL!");
	printf("buf is :%s\n", buf);
	
	ret = select(fd + 1, &rds, NULL, NULL, NULL);
	if (ret < 0){
		printf("select error!\n");
		exit(1);
	}
	
	if (FD_ISSET(fd, &rds))
		read(fd, buf, sizeof(buf));
		
	printf("read buf:%s\n", buf);
	
	close(fd);
	
	return 0;
	
}
	