// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <linux/input.h>

// int main(void)
// {
// 	struct input_event ev;
// 	ssize_t rsize = 0;
// 	int fd = 0;
// 	int x,y = 0;

// 	/* 1. 打开输入设备文件 */
// 	fd = open("/dev/input/event0",O_RDWR);
// 	if(-1 == fd)
// 	{
// 		perror("open event0 error");
// 		return -1;
// 	}
	
// 	/* 2. 读取输入事件（读取一个struct input_event结构体数据 */
// 	while(1)
// 	{
// 		rsize = read(fd,&ev,sizeof(ev));
// 		if(-1 == rsize)
// 		{
// 			perror("read event0 error");
// 			close(fd);
// 			return -1;
// 		}
// 		if(sizeof(ev) == rsize)			/* 读取到一个输入事件 */
// 		{
// 			printf("ev.type:%x\tev.code:%x\tev.value:%d\n",ev.type,ev.code,ev.value);
// 			/* 3. 根据输入事件结构体中的成员变量的数值，判定获取到输入事件 */
// 			if(ev.type == EV_KEY)		/* 按键事件 */
// 			{
// 				if(ev.code == KEY_F1)	/* F1按键触发的事件 */
// 				{
// 					if(ev.value!=0)		/* 按键按下 */
// 					{

// 					}
// 					else				/* 按键松开 */
// 					{

// 					}	
// 				}
// 				else if(ev.code == BTN_TOUCH)	/* 触摸屏当作按键，触发的事件 */
// 				{
// 					if(ev.value!=0)		/* 按键按下 */
// 					{
// 						printf("用户在坐标(%d,%d)处点击触摸屏\n",x,y);
// 					}
// 					else				/* 按键松开 */
// 					{
// 						printf("用户在坐标(%d,%d)处松开触摸屏\n",x,y);
// 					}
// 				}
// 			}
// 			else if(ev.type == EV_ABS)	/* 触摸屏事件 */
// 			{
// 				if(ev.code == ABS_X)	/* 触摸点X轴坐标事件 */
// 				{
// 					x = ev.value;		/* 此时value是X轴坐标 */
// 				}
// 				else if(ev.code==ABS_Y) /* 触摸点Y轴坐标事件 */
// 				{
// 					y = ev.value;		/* 此时value是Y轴坐标 */
// 				}
// 			}
// 			else if(ev.type == EV_SYN)	/* 同步事件 */
// 			{

// 			}
// 			else if(ev.type == EV_REL)	/* 相对坐标事件（鼠标） */
// 			{

// 			}
// 		}
	
// 	}


// 	/* 关闭文件 */
// 	close(fd);
// }
