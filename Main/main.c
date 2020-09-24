#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(2)
typedef struct BMP_Head{
	short FILE_NAME; //ͷ�ļ��ĵ����֣���BMPλͼ�и�ֵΪ'B''M' 
	int FILE_SIZE; //�ļ��Ĵ�С 
	short RESERVE_ONE; //��һ������λ 
	short RESERVE_TWO; //�ڶ�������λ 	
	int HEAD_SIZE;  //ͷ�ļ��Ĵ�С 
	
	int INFORMATION_SIZE; // ��Ϣͷ�ļ��Ĵ�С 
	int WIDTH; //ͼ��Ŀ� 
	int HEIGHT; //ͼ��ĸ� 
	short PLANE; //˵��λ���� 
	short PIXEL_COLOR; //ÿ��������ռ��ɫλ�� 
	int IF_COMPRESS;  //�Ƿ����ѹ�� 
	int DATA_SIZE;  //�����ļ��Ĵ�С 
	int HORIZONTAL_RESOLUTION;  //ˮƽ�ֱ��� 
	int VERTICAL_RESOLUTION;  // ��ֱ�ֱ��� 
	int COUNT_COLOR;  // ʹ����ɫ�ĸ��� 
	int IMPORTANT_COLOR;  //�Ƿ�����Ҫ����ɫ 
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
		
		printf("����������Ϊ��ͼƬ�ĸ�");
		scanf("%d",&Height);
		printf("����������Ϊ��ͼƬ�Ŀ�"); 
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
		printf("ͼƬ�Ƿ�����?");
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
		
			printf("��ӭ�´�ʹ��");
			break;
		}
		else
		{
			continue;
		}
	}
	return 0;
}
