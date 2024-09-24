#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>

int get_touch_event(int page)
{
    int a = 0;
    int b = 0;
    struct input_event ev;
    //打开linux的输入设备文件
    int file = open("/dev/input/event0",O_RDWR);
    size_t num = 0;
    if (file == -1) {
        perror("FIle Open fail");
        close(file);
        return -1;
    }
    while (1)
    {
        int x,y;
        int num = read(file,&ev,sizeof(ev));
        //读取输入设备文件，获取触摸事件信息
        if (num == -1) {
            perror("File read failed");
            close(file);
            return -1;
        }
        //解析触摸事件信息，获取触摸坐标、按压状态等信息
        if (num == sizeof(ev))
        {
            if (ev.type == EV_KEY && page == 0) 
            {
                if (ev.code == KEY_F1)
                {
                    if (ev.value != 0)
                        {
                            printf("按钮按下");
                            return 1;
                        }
                    else 
                        {
                            printf("按钮松开");
                            return 1;
                        }
                }
                else if (ev.code == BTN_TOUCH) 
                    {
                        if (ev.value != 0)
                        {
                            printf("\n");
                            printf("按钮按下,x:%d,y:%d",x,y);
                            a = x;
                            b = y;
                            if(x>320 && x<600 && y>90 && y<250)
                            {
                                return 3;
                            }
                            else if(x>350 && x<600 && y>350 && y<500)
                            {
                                return 4;
                            }
                            else if(x>50 && x<280 && y>70 && y<680)
                            {
                                return 6;
                            }
                            else if(x>700 && x<800 && y>70 && y<200)
                            {
                                return 12;
                            }
                        }
                            else 
                            {
                                printf("按钮松开,x:%d,y:%d",a,b);
                                // if(x-a>0)
                                // {
                                //     return 1;
                                // }
                                // else if(x-a<0)
                                // {
                                //     return 2;
                                // }
                                // if(y-b>0)
                                // {
                                //     return 1;
                                // }
                                // else if(y-b<0)
                                // {
                                //     return 2;
                                // }
                            }
                    }
            }
            else if (ev.type == EV_KEY && page == 1)
            {
                 if (ev.code == KEY_F1)
                {
                    if (ev.value != 0)
                        {
                            printf("按钮按下");
                            return 1;
                        }
                    else 
                        {
                            printf("按钮松开");
                            return 1;
                        }
                }
                else if (ev.code == BTN_TOUCH) 
                    {
                        if (ev.value != 0)
                        {
                            printf("\n");
                            printf("按钮按下,x:%d,y:%d",x,y);
                            a = x;
                            b = y;
                            
                            if(x>0 && x<100 && y>0 && y<100)
                            {
                                return 5;
                            }
                        }
                            else 
                            {
                                printf("按钮松开,x:%d,y:%d",a,b);
                                if(x-a>0)
                                {
                                    return 1;
                                }
                                else if(x-a<0)
                                {
                                    return 2;
                                }
                                if(y-b>0)
                                {
                                    return 1;
                                }
                                else if(y-b<0)
                                {
                                    return 2;
                                }
                            }
                    }
            }

            else if (ev.type == EV_KEY && page == 2)
            {
                 if (ev.code == KEY_F1)
                {
                    if (ev.value != 0)
                        {
                            printf("按钮按下");
                            return 1;
                        }
                    else 
                        {
                            printf("按钮松开");
                            return 1;
                        }
                }
                else if (ev.code == BTN_TOUCH) 
                    {
                        if (ev.value != 0)
                        {
                            printf("\n");
                            printf("按钮按下,x:%d,y:%d",x,y);
                            a = x;
                            b = y;
                            if(x>0 && x<100 && y> 0 && y<100)
                            {
                                return 9;
                            }
                            else if(x>350 && x<450 && y>400 && y<520)
                            {
                                return 10;
                            }
                            else if(x>560 && x<660 && y>400 && y<520)
                            {
                                return 11;
                            }
                        }
                            else 
                            {
                                printf("按钮松开,x:%d,y:%d",a,b);
                            }
                    }
            }
                else if (ev.type == EV_ABS) 
                {
                    if (ev.code == ABS_X) 
                    {
                        x = ev.value;
                    }
                    else if (ev.code == ABS_Y) 
                    {
                    y = ev.value;
                    }
                }

            // else if (ev.type == EV_SYN) {
            //     if (ev.code == SYN_REPORT) {
            //         printf("同步事件");
            //     }
            //     else if (ev.code == SYN_DROPPED) {
            //         printf("丢弃事件");
            //     }
            // }
            }
            //关闭输入设备文件
    
    }
    close(file);
    return 0;
}