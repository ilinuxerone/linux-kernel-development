#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE  *fp = NULL;
	char buf[4096];
	
	strcpy(buf, "memdev is char dev!");
	printf("buf :%s\n", buf);
	
	fp = fopen("/dev/memdev0", "r+");
	if (NULL == fp){
		fprintf(stderr, "open memdev0 error!\n");
		return -1;
	}
	
	strcpy(buf, "buf is null!\n");
	printf("read buf:%s\n", buf);
	
	fread(buf, sizeof(buf), 1, fp);
	
	printf("read buf:%s\n", buf);
	fclose(fp);
	
	return 0;
}	