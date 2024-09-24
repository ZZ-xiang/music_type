#include "ev.h"
#include "pm.h"
#include "bmp.h"

int state[12][13]={0};
 
int jud(int a,int b,int c)
{
	int num=0;
	if(state[a][b]==c)
	{
		for(int i=0;i <= 12;i++)        //判断横
		{
			if(state[a][i]==c)
			{
				num++;
				if(num == 5)
 
				{
					Show_Bmp("xiao.bmp");
					return 2;
					break;
				}
			}
			else num=0;
		}
 
		for(int i=0;i <= a+4;i++)        //判断竖
		{
			if(state[i][b]==c)
			{
				num++;
				if(num == 5)
 
				{
					Show_Bmp("xiao.bmp");
					return 2;
					break;
				}
			}
			else num=0;
		}
 
		if(a<=b)                        //判断左上到右下
		{
			for(int i=0,j=b-a;i<12 && j<13;i++,j++)
			{
				if(state[i][j]==c)
				{
					num++;
					if(num == 5)
 
					{
						Show_Bmp("xiao.bmp");
						return 2;
						break;
					}
				}
				else num=0;
			}
		}
		else if(a>b)                     //判断左上到右下
		{   
			for(int j=0,i=a-b;i<12 && j<13;i++,j++)
			{
				if(state[i][j]==c)
				{
					num++;
					if(num == 5)
 
					{
						Show_Bmp("xiao.bmp");
						return 2;
						break;
					}
				}
				else num=0;
			}
		}
		
		if(a>=b)     //判断右上到左下
		{
			for(int i=a+b,j=0;i>=0;i--,j++)
			{
				if(state[i][j]==c)
				{
					num++;
					if(num == 5)
 
					{
						Show_Bmp("xiao.bmp");
						return 2;
						break;
					}
				}
				else num=0;
			}
		}
		if(b>a)     //判断右上到左下
		{
			for(int i=11,j=b+a-11;j<=12;i--,j++)
			{
				if(state[i][j]==c)
				{
					num++;
					if(num == 5)
 
					{
						Show_Bmp("xiao.bmp");
						return 2;
						break;
					}
				}
				else num=0;
			}
		}
	}
}
 
int Get_ev(int *x,int *y)
{
	int fd = open("/dev/input/event0",O_RDONLY);
	if(-1 == fd)
	{
		perror("open error");
		return -1;
	}
	struct input_event ev;
	int x1,y1,q=0,w;
	while(1)
	{
		read(fd,&ev,sizeof(ev));
		printf("ev_type = %d code = %d value = %d\n",ev.type,ev.code,ev.value);	
		if(ev.type == EV_ABS)
		{
			if(ev.code == 0)//x
			{
				x1 = ev.value;
			}
			else
			{
				y1 = ev.value;
			}
		}
		if(ev.type == EV_KEY && ev.code == 330 && ev.value == 1)//保存初始坐标
		{
			*x = x1;
			*y = y1;
		}
		//点击
		if(ev.type == EV_KEY && ev.code == 330 && ev.value == 0)
		{
			if(*x == x1 && *y == y1)//点击
			{   
				printf("dianji\n");
				Dis_pan();
				Dis_xian();
				break;
			}
		}
	}
 
	while(1)
	{
		read(fd,&ev,sizeof(ev));
		printf("ev_type = %d code = %d value = %d\n",ev.type,ev.code,ev.value);	
		if(ev.type == EV_ABS)
		{
			if(ev.code == 0)//x
			{
				x1 = ev.value;// 1024
			}
			else
			{
				y1 = ev.value;
			}
		}
		if(ev.type == EV_KEY && ev.code == 330 && ev.value == 1)//保存初始坐标
		{
			*x = x1;
			*y = y1;
		}
		//点击
		if(ev.type == EV_KEY && ev.code == 330 && ev.value == 0)
		{
			if(*x == x1 && *y == y1)//点击
			{
				printf("dianji\n");
				for(int i = 20;i <= 460;i+=40)
				{
					for(int j = 50;j <= 650;j+=50)
					{
						int a,b;
						a=(i-20)/40;
						b=(j-50)/50;
						if(q == 0 && (*x - j)*(*x - j) + (*y - i)*(*y - i) < 400 && state[a][b] == 0)
						{
							Dis_heizi(i, j);
							state[a][b]=1;
							printf("%d--%d--%d",a,b,state[a][b]);
							w = jud(a,b,1);
							q++;
							break;
						}
						else if(q == 1 && (*x - j)*(*x - j) + (*y - i)*(*y - i) < 400 && state[a][b] == 0)
						{
							Dis_baizi(i, j);
							state[a][b]=2;
							w = jud(a,b,2);
							q--;
							break;
						}
					}
					if(w == 2) break;
				}
			}
		}
	}
}