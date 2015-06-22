#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char buf[4096];
	
	fp = fopen("/dev/memdev0", "r+");
	if (NULL == fp){
		fprintf(stderr, "open dev memdev0 error!\n");
		return -1;
	}
	
	strcpy(buf, "memdev is char dev!");
	printf("write buf :%s\n", buf);
	
	fwrite(buf, sizeof(buf), 1, fp);
	
	sleep(5);
	fclose(fp);
	
	return 0;
	
}