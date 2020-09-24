#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

int main(int argc, char *argv[]) {
	FILE *fp,*fp_temp;
	unsigned char *p1;
	char temp;
	int i;
	fp = fopen("test.bmp","rb");
	fp_temp = fopen("temp.bmp","wb");
	fseek(fp,28,SEEK_SET);
	temp = fgetc(fp);
	if(temp!=24)
	{
		printf("该图不是24bitBMP图片，无法进行后续步骤");
		exit(0);
	}
	fseek(fp,54,SEEK_SET);
	do
	{
		temp = fgetc(fp);
		if(temp!=EOF)
		{
			fputc(temp,fp_temp);
		}
	}while(temp!=EOF);
	fclose(fp);
	fclose(fp_temp);
	fp = fopen("test.bmp","wb");
	fp_temp = fopen("temp.bmp","rb");
	do
	{
		temp = fgetc(fp_temp);
		if(temp!=EOF)
		{
			fputc(temp,fp);
		}
	}while(temp!=EOF);
	fclose(fp);
	fclose(fp_temp);
	return 0;
}

