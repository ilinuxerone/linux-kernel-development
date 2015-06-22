#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp0 = NULL;
	char  buf[4096];
	
	strcpy(buf, "mem is char dev!");
	printf("buf : %s\n", buf);
	
	fp0 = fopen("/dev/memdev0", "r+");
	if (NULL == fp0){
		fprintf(stderr, "open memdev0 error!\n");
		return -1;
	}
	
	fwrite(buf, sizeof(buf), 1, fp0);
	
	fseek(fp0, 0, SEEK_SET);
	
	strcpy(buf, "buf is NULL");
	printf("buf : %s\n", buf);
	
	fread(buf, sizeof(buf), 1, fp0);
	printf("buf: %s\n", buf);
	
	return 0;	
}