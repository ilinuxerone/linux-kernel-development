/*��������
*ǰ�����Ѿ������豸�ļ������ַ���1��mknod 2 class_create() device_create()
*�豸�ļ�һ����/dev/Ŀ¼�´���������Ŀ¼Ҳ���ԣ����Կ���ͨ������
*mknod -m 0666 /dev/memdev0 c 255 0
*
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE   *fp0 = NULL;
	char buf[4096];
	
	strcpy(buf, "Mem is char dev!");
	printf("Buf: %s\n", buf);
	
	fp0 = fopen("/dev/memdev0", "r+");
	if (NULL == fp0){
		fprintf(stderr, "open memdev0 error!\n");
		return -1;
	}
	
	fwrite(buf, sizeof(buf), 1, fp0);
	
	fseek(fp0, 0, SEEK_SET);
	
	strcpy(buf, "buf is NULL!");
	printf("buf : %s\n", buf);
	
	fread(buf, sizeof(buf), 1, fp0);
	printf("buf:%s\n", buf);
	
	return 0;
}