#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(2)
typedef struct BMP_Head{
	short FILE_NAME; //头文件的的名字，在BMP位图中该值为'B''M' 
	int FILE_SIZE; //文件的大小 
	short RESERVE_ONE; //第一个保留位 
	short RESERVE_TWO; //第二个保留位 	
	int HEAD_SIZE;  //头文件的大小 
	
	int INFORMATION_SIZE; // 信息头文件的大小 
	int WIDTH; //图像的宽 
	int HEIGHT; //图像的高 
	short PLANE; //说明位面数 
	short PIXEL_COLOR; //每个像素所占颜色位数 
	int IF_COMPRESS;  //是否进行压缩 
	int DATA_SIZE;  //数据文件的大小 
	int HORIZONTAL_RESOLUTION;  //水平分辨率 
	int VERTICAL_RESOLUTION;  // 垂直分辨率 
	int COUNT_COLOR;  // 使用颜色的个数 
	int IMPORTANT_COLOR;  //是否有重要的颜色 
}BMPHEAD;

int main(int argc, char *argv[]) {
	char key;
	FILE *fp;
	FILE *fp_temp;
	BMPHEAD bmp_head;
	char *p;
	char temp;
	int Width,Height;
	long Data_Size;
	while(1)
	{
		fp_temp = fopen("temp.bmp","wb");
		fp = fopen("test.bmp","rb");
		
		fseek(fp,0,SEEK_END);
		Data_Size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		
		printf("请输入你认为的图片的高");
		scanf("%d",&Height);
		printf("请输入你认为的图片的宽"); 
		scanf("%d",&Width);
		
		bmp_head.FILE_NAME = 'B'+'M'*256;
		bmp_head.FILE_SIZE = 54 + Data_Size;
		bmp_head.RESERVE_ONE = 0;
		bmp_head.RESERVE_TWO = 0;
		bmp_head.HEAD_SIZE = 54;
		bmp_head.INFORMATION_SIZE = 40;
		bmp_head.WIDTH = Width;
		bmp_head.HEIGHT = Height;
		bmp_head.PLANE = 1;
		bmp_head.PIXEL_COLOR = 24;
		bmp_head.IF_COMPRESS = 0;
		bmp_head.DATA_SIZE = Data_Size;
		bmp_head.HORIZONTAL_RESOLUTION = 0;
		bmp_head.VERTICAL_RESOLUTION = 0;
		bmp_head.COUNT_COLOR = 0;
		bmp_head.IMPORTANT_COLOR = 0;
		
		fwrite(&bmp_head,1,sizeof(BMPHEAD),fp_temp);
		fclose(fp_temp);
		fp_temp = fopen("temp.bmp","ab");
		
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
		
		while(getchar()!='\n');
		printf("图片是否正常?");
		scanf("%c",&key);
		if(key == 'y' || key == 'Y')
		{
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
		
			printf("欢迎下次使用");
			break;
		}
		else
		{
			continue;
		}
	}
	return 0;
}
