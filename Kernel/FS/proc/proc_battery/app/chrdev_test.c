#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;

	fd = open("/dev/demo_cdev", 666);

	ioctl(fd, F_GETFD, 0 );

	
	close(fd);

	return 0;
}


