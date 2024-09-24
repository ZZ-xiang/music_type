#include <stdio.h>
#include "pm.h"
 
 
unsigned int *plcd =NULL;
 
void Display( int color,int x,int y)
{
	if(x >= 0 && x <=800 && y >= 0 && y <= 480){
		*(plcd + y * 800 + x) = color;
	}
}
 
void se()
{
	
	int fd = open("/dev/fb0",O_RDWR);
	if(fd == -1)
	{
		perror("open error");
	}
	int color[10] = {0x10900,0xff00ff,0xf0394f,0xf009ba9f,0xf066f3,0x856fa,0x9392c83b};
	int j=0;
	while(1){
		for(int i=0;i<384000;i++){
			int w = write(fd,&color[j],4);
			if(-1 == w)
			{
				perror("write error");
			}
		}
		sleep(2);
		j++;
		if(j==7) j=0;
 
		lseek(fd,0,SEEK_SET);//定位光标在文件头
	}
}
 
// int Lcd_Init()
// {
// 	int fd = open("/dev/fb0",O_RDWR);
// 	if(fd == -1){
// 		perror("open error");
// 		return -2;
// 	}
// 	plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	
 
void Dis_wh()
{
	//int color[10] = {0x190f0,0xff00ff,0xff,0xff0000ff,0xf0f083,0x8596fa,0x298c83b};
	//int q=0;
	//while(1){
		for (int i = 0;i <= 880;i++){
			for(int j = 0;j < 480;j++){
				//int p = 
				if(((i-400)*(i-400) + (j-240)*(j-240) - 1)*((i-400)*(i-400) + (j-240)*(j-240) - 1)*((i-400)*(i-400) + (j-240)*(j-240) - 1)< (i-400)*(i-400) - (j-240)*(j-240)){
					Display(0xf0f083, i, j);
				}
			}
		//}
		//sleep(2);
		//q++;
		//if(q==7) q=0;
	}
}
 
//画图片
int Dis_pic(char *pic)
{
	int fd = open(pic,O_RDONLY);
	if(-1 == fd)
	{
		perror("open error");
		return -1;
	}
	int width,heigh;
	short depth;
	lseek(fd,0x12,SEEK_SET);
	read(fd,&width,4);
	read(fd,&heigh,4);
	lseek(fd,0x1c,SEEK_SET);
	read(fd,&depth,2);
	printf(" %d  %d  %d\n",width,heigh,depth);
	int laizi;
	unsigned char color_buf[width * heigh * depth / 8];//32 24 
	char color_a = 0,color_r,color_g,color_b; //颜色分量
	unsigned int color;//像素点的颜色
	char *p = color_buf;
	lseek(fd,0x36,SEEK_SET);
	read(fd,color_buf,width * heigh * depth / 8);
	for(int i = heigh - 1;i >= 0;i--)
	{
		for(int j = 0;j < width;j++)
		{
			color_b = *p++;//b颜色
			color_g = *p++;
			color_r = *p++;
			if(32 == depth)
			{
				color_a = *p++;
			}
			color = color_a << 24 | color_r << 16 | color_g << 8 | color_b;//屏幕需要的颜色a r g b
			Display(color, j, i);
		}
	}
}
 
void Dis_pan()
{
	for(int i = 0;i < 800;i++){
		for(int j = 0;j < 480;j++){
			Display(0xf0f00f, i, j);
		}
	}
}
 
void Dis_xian()
{
	for(int i = 50;i <= 650;i+=50){
		for(int j = 20;j < 460;j++){
			Display(0x0, i, j);
		}
	}
	for(int i = 20;i <= 460;i+=40){
		for(int j = 50;j < 650;j++){
			Display(0x0, j, i);
		}
	}
}
 
void Dis_baizi(int x,int y)
{
	for(int i = 0;i < 480;i++){
		for(int j = 0;j < 800;j++){
			if((i-x)*(i-x) + (j-y)*(j-y)<170)
			{
				Display(0xffffff, j, i);
			}
		}
	}
}
 
void Dis_heizi(int x,int y)
{
	for(int i = 0;i < 480;i++){
		for(int j = 0;j < 800;j++){
			if((i-x)*(i-x) + (j-y)*(j-y)<170)
			{
				Display(0x0, j, i);
			}
		}
	}
}
 