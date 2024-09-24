#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"DoubleList.h"
#include"bmp.h"
#include"lcd.h"
#include<unistd.h>
#include<pthread.h>
#include<linux/input.h>
#include "Touch.h"
#include"ev.h"
#include"pm.h"
List* initList() {
    List* list = (List*)malloc(sizeof(List));
    list->data = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}


int isEmpty(List* list) {
    return list->head == NULL;
}


List* insertElement(List* list, Element data)
 {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->pre = NULL;
    if (isEmpty(list)) 
    {
        list->head = node;
        list->tail = node;
        node->next = node;
        node->pre = node;
        list->data = list->data + 1;
        return list;
    } 
    else 
    {
        node->next = list->head;
        node->pre = list->tail;
        list->head->pre = node;
        list->tail->next = node;
        list->tail = node;
        list->data = list->data + 1;
        return list;
    }
    return list;
    
}


List* DeleteNode(List* list, Element data) {
    if (isEmpty(list)) {
        return NULL;
    }

    Node* flag = list->head;
    while (flag) {
        if (flag->data == data) {
            if (list->data == 1) {
                list->head = NULL;
                list->tail = NULL;
                list->data = list->data - 1;
                free(flag);
                return list;
            }
            if (flag == list->head) {
                list->head = flag->next;
                list->head->pre = list->tail;
                list->tail->next = list->head;
            } else if (flag == list->tail) {
                list->tail = flag->pre;
                list->tail->next = list->head;
                list->head->pre = list->tail;
            } else {
                flag->pre->next = flag->next;
                flag->next->pre = flag->pre;
            }
            free(flag);
            list->data = list->data - 1;
            return list;
        }
        flag = flag->next;
        if (flag == list->head) {
            break;
        }
    }
    return list;
}

void Slide_Bmp(Node* pnow,List* list)
{ 
    Show_Bmp(pnow->data);
   //Node* pnew = pnow;
     while(pnow) 
            {
                printf("Data: %s\n", pnow->data);
               
                my_exit_huace();
                int b = get_touch_event(1);
                if(b == 1)
                {
                    printf("Touch event detected.\n");
                    printf("Data: %s\n", pnow->data);
                    Show_Bmp(pnow->data);
                    pnow = pnow->next;
                }
                else if(b == 2)
                {
                    printf("Touch event detected.\n");
                    printf("Data: %s\n", pnow->data);
                    Show_Bmp(pnow->data);
                    pnow = pnow->pre;
                }
                else if(b == 5)
                {
                    printf("Touch event detected.\n");
                    printList(list,".");
                    break;
                }
        }
}


void autocycle_Bmp(Node* pnow,List* list)
{           
   
    Node* pnew = pnow;
        while(1)
        {
            
            Show_Bmp(pnew->data);
            pnew = pnew->next;
            //myexit();
            usleep(1500000);
            if(pnew == list->head)
            {
                printList(list,".");
                break;
            }
        }
}

//从头播放音乐
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int playing = 0; // 0 表示暂停，1 表示播放
void* music(void* argc) {
        //pthread_mutex_lock(&mutex);
        while(1)
        {
            if (playing == 0) {
                system("killall -9 madplay");
                int result = system("madplay Music.mp3");
                if (result == -1) {
                    perror("Failed to play music");
                } else {
                    printf("Music played.\n");
                    playing = 1;
                    break;
                }
            }
            else if (playing == 1) {
                int result = system("killall -STOP madplay");
                if (result == -1) {
                    perror("Failed to pause music");
                } else {
                    //system("killall -STOP madplay");
                    playing = 0;
                    break;
                }
            }
        }
        //pthread_mutex_unlock(&mutex);
     //sleep(1); // 避免忙等待
}

//下一首音乐播放
void* next_music(void* argc) 
{
    char* path = (char*)argc;
    static int current_index = 1; // 静态变量，用于记录当前播放的索引
    int count;
    char** file = Find_File_MP3(path, &count);
    if (file == NULL) {
        // 处理文件查找失败的情况
        perror("Failed to find file");
        return NULL;
    }

    char** file1 = (char**)malloc(count * sizeof(char*));
    if (file1 == NULL) {
        // 处理内存分配失败的情况
        free(file);
        perror("Failed to allocate memory");
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        file1[i] = strdup(file[i]); // 使用 strdup 复制字符串
        if (file1[i] == NULL) {
            // 处理内存分配失败的情况
            perror("Failed to duplicate string");
            for (int j = 0; j < i; j++) {
                free(file1[j]);
            }
            free(file1);
            free(file);
            return NULL;
        }
    }

    // for (int i = 0; i < count; i++) {
    //     printf("%s\n", file1[i]); // 使用 %s 打印字符串
    // }
    if (get_touch_event(2) == 11) {
        char command[256];
        snprintf(command, 256, "madplay %s", file1[current_index]);
        system("killall -9 madplay");
        printf("Playing %s\n", file1[current_index]); // 使用 current_index
        system(command);
        current_index = (current_index + 1) % count; // 更新索引，循环播放
    }
    else if (get_touch_event(2) == 12) { // 检测到暂停事件
            system("killall -STOP madplay");
            printf("Music paused.\n");
             // 退出循环，保持当前索引不变
        }
    // 释放内存
    for (int i = 0; i < count; i++) {
        free(file1[i]);
    }
    free(file1);
    free(file);

    return NULL;
}

void MusicPlayer(List* list, char* path) {
    List* list1 = list;
    
    while (1) {
        printf("a == 5\n");
        Show_Bmp("../index.bmp");
        int d = get_touch_event(2);
        if (d == 9) {
            printList(list1, ".");
            break;
        }
        else if (d == 10)
        {
            // while(1)
            // {
                //int a = get_touch_event(2);
                pthread_t pid;
                if(pthread_create(&pid, NULL, music, NULL) == -1)
                {
                    perror("Failed to create thread");
                    return;

                }
        //}
        }
        else if (d == 11)
        { // 下一首音乐
           pthread_t p;
           if(pthread_create(&p, NULL, next_music, path) == -1)
           {
               perror("Failed to create thread");
               return;
           }
        else
            {
                continue;
            }
}
}
}

void GamePlayer(Node* pnow)
{           
    int x,y;
    Show_Bmp("gqj1.bmp");  //写入游戏开始界面                                                             
    Get_ev(&x,&y);
}

void printList(List* list,char* path) {
    if (isEmpty(list)) {
        printf("List is empty.\n");

    }
    Node* pnow = list->head;
    //创建一个进程以及进程id = 1；
    //login(); // 调用登录界面
    login(); // 调用登录界面
    int a = get_touch_event(0); // 调用触摸事件
    //printf("a = %d",a);
    if(a == 3)
    {
        autocycle_Bmp(pnow,list);
    }
    else if(a == 4)
    {
        Slide_Bmp(pnow,list);
    }
    else if(a == 6)
    {
        MusicPlayer(list,".");
    }
    else if(a == 12)
    {
        GamePlayer(pnow);
    }
    else
    {
        printList(list,".");
        printf("Touch event detected.\n");
    }

}