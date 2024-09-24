#include<stdio.h>
#include<sys/fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include"lcd.h"
#include"DoubleList.h"
#include"bmp.h"
#include "Touch.h"
#include <linux/input.h>
#include <pthread.h>

// void* music_play(void* arg)
// {
// 	while(1)
// 	{
// 		//myexit();
// 		// system("madplay Music.mp3");
// 		// sleep(5);
// 	}
// }


int main(int argc, char* argv[])
{
    //printf("hahahahahahahahaahahahahahaah\n\n");
    List* list = initList(); // 创建双向链表
    if(argc != 2)
    {
        // 判断参数是否正确？
        printf("参数不正确！请按照格式-./绝对路径- -文件名- 输入\n"); 
        return -1; 
    }
    
    //建立映射
    if(initlcd())
    {
        printf("LCD初始化失败！\n");
        return -1;
    }
    
    // pthread_t music_thread;
    // if(pthread_create(&music_thread, NULL, music_play, NULL) == -1)
    // {
    //     perror("pthread_create");
    //     return -1;
    // } // 创建线程

    Find_File(argv[1], list);
    printList(list,argv[1]); // 打印双向链表
    uninitlcd(); // 释放映射
    return 0;   
}