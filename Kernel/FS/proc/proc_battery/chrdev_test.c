#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	char buf[1024];
	int n;

	fd = open("/proc/power/battery_status", 666);
	

	n = read(fd, buf, 1024);
	buf[n] = 0;
	printf("read %s\n", buf );	

//	ioctl(fd, F_GETFD, 0 );

	
	close(fd);

	return 0;
}


