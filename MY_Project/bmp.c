#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "DoubleList.h"
#include "bmp.h"
#include "lcd.h"
/*
*读取文件并找到后缀名为.bmp的文件绝对路径文件名
*/
//测试无问题

int Find_File(char* path,List* list) 
{
    DIR *dir;
    struct dirent *p;
    struct stat st;
    char* arr = NULL;
    // 假设 path 已经被正确初始化
    dir = opendir(path);
    if (!dir) {
        perror("opendir error");
        return -1;
    }

    while ((p = readdir(dir))) {
		arr = (char*)malloc(strlen(path)+256+2);
        // 将读取到的绝对路径存进 arr 数组中
        snprintf(arr, strlen(path) + strlen(p->d_name) + 2, "%s/%s", path, p->d_name);

        // 判断 arr 是否为普通路径
        if (lstat(arr, &st) == -1) {
            perror("lstat error");
            closedir(dir);
            return -1;
        }

        if ((st.st_mode & S_IFMT) == S_IFREG) {
            // 为普通文件
            if ((strstr(p->d_name, ".bmp") != NULL) && (strcmp(strstr(p->d_name, ".bmp"), ".bmp") == 0)) {
                // 为 .bmp 结尾的文件
                printf("%s\n", arr);
                // 将文件绝对路径存入双向链表中
                insertElement(list, (Element)arr);
            }
        }
    }

    closedir(dir);
    return 0;
}

char** Find_File_MP3(char* path, int* count) {
    char arr1[1024];
    DIR *dir;
    struct dirent *p;
    struct stat st;
    char arr[1024];
    int i = 0;

    // 假设 path 已经被正确初始化
    dir = opendir(path);
    if (!dir) {
        perror("opendir error");
        return NULL;
    }

    // 动态分配内存
    char** a = (char**)malloc(10 * sizeof(char*));
    if (!a) {
        perror("malloc error");
        closedir(dir);
        return NULL;
    }

    while ((p = readdir(dir))) {
        // 将读取到的绝对路径存进 arr 数组中
        snprintf(arr, strlen(path) + strlen(p->d_name) + 2, "%s/%s", path, p->d_name);

        // 判断 arr 是否为普通路径
        if (lstat(arr, &st) == -1) {
            perror("lstat error");
            closedir(dir);
            free(a);
            return NULL;
        }

        if ((st.st_mode & S_IFMT) == S_IFREG) {
            // 为普通文件
            if ((strstr(p->d_name, ".mp3") != NULL) && (strcmp(strstr(p->d_name, ".mp3"), ".mp3") == 0)) {
                // 为 .mp3 结尾的文件
                // 将文件绝对路径存入数组中
                snprintf(arr1, strlen(path) + strlen(p->d_name) + 2, "%s/%s", path, p->d_name);
                a[i] = (char*)malloc((strlen(arr1) + 1) * sizeof(char));
                if (!a[i]) {
                    perror("malloc error");
                    closedir(dir);
                    for (int j = 0; j < i; j++) {
                        free(a[j]);
                    }
                    free(a);
                    return NULL;
                }
                strcpy(a[i], arr1);
                i++;
            }
        }
    }

    closedir(dir);
    *count = i; // 返回找到的文件数量
    return a;
}


// �g���g��ou2
// 打印出文件头部信息 大小宽度高度位深度
 int Show_Bmp(char* path)
{
    //计算高度宽度位深度
	//打开文件
	int fd;
	int address = 0;
	int buf[4] = {0};
	//定义文件长度
	int file_len = 0;
	//定义文件头部信息结构体
	struct
	{
		int dib_size;
		int w;
		int h;
		short pms;
		short pix_bit;
		int tar_mode;
		int pix_size;
		int x_fbl;
		int y_fbl;
		int tsb_num;
		int zy_num;
	}DIB_data;

	fd = open(path,O_RDWR);
	if(fd == -1)
	{
		perror("open error");
		return -1;
	}
	//读取文件头部信息
	//光标定位到需要读的位置处
	lseek(fd,0x02,SEEK_SET);
	if(read(fd,buf,4) == -1)
	{
		perror("read error");
		return -1;
	}
	file_len = buf[0] | buf[1]<<8 | buf[2]<<16 | buf[3]<<24;
	printf("size of file:%d\n",file_len);

	//光标定位到需要读的位置处,头部信息
	lseek(fd,0x0E,SEEK_SET);
	if(read(fd,&DIB_data,40) == -1)
	{
		perror("read error");
		return -1;
	}
	printf("文件的宽度为：%d,文件的高度为:%d,文件的位深度为:%d\n",DIB_data.w,DIB_data.h,DIB_data.pix_bit);

	//打印出文件头部信息
	lseek(fd,0x0A,SEEK_SET);
	if(read(fd,&address,sizeof(int)) == -1)
	{
		perror("read error");
		return -1;
	}
	printf("文件头部信息的地址为：%d\n",address);

	unsigned char* p = NULL;
	p = (unsigned char*)malloc(DIB_data.h*DIB_data.w*DIB_data.pix_bit/8);
	int i = 0;
	int x,y;
	int color = 0;
	unsigned char a,r,g,b;
	//定位坐标
	lseek(fd,address,SEEK_SET);

	if(read(fd,p,DIB_data.h*DIB_data.w*DIB_data.pix_bit/8) == -1)
	{
		perror("read error");
		close(fd);
		return -1;
	}

	for(int y = 0; y<abs(DIB_data.h); y++)
	{
		for(int x = 0;x<abs(DIB_data.w);x++)
		{
			if(DIB_data.pix_bit == 24)
			{
				b = p[i++];
				g = p[i++];
				r = p[i++];
				a = 0;
				color = a<<24 | r<<16 | g<<8 | b;

				DrawPoint(DIB_data.w>0?x:(DIB_data.w-1-x),
						 DIB_data.h<0?y:(DIB_data.h-1-y),
						  color);
			}
			else if(DIB_data.pix_bit == 32)
			{
				b = p[i++];
				g = p[i++];
				r = p[i++];
				a = p[i++];                         
				color = a<<24 | r<<16 | g<<8 | b;
				DrawPoint(DIB_data.w>0?x:(DIB_data.w-1-x),
				DIB_data.h<0?y:(DIB_data.h-1-y),color);
			}
		}
	}
	
	return 0;
}