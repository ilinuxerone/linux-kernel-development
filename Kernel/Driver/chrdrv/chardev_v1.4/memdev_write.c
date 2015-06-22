#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE   *fp = NULL;
	char  buf[128];
	
	fp = fopen("/dev/memdev0", "r+");
	if (fp == NULL){
		printf("open dev memdev error\n");
		return -1;
	}
	
	strcpy(buf, "memdev is char dev!");
	printf("buf is:%s\n", buf);
	fwrite(buf, sizeof(buf), 1, fp);
	
	sleep(5);
	fclose(fp);
	
	return 0;
	
}