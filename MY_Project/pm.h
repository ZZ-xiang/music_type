#ifndef __PM_H__
#define __PM_H__
 
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
 
void se();
int Lcd_Init();
void Dis_wh();
void Display( int color,int x,int y);
int Dis_pic(char *pic);
void Dis_pan();
void Dis_xian();
void Dis_baizi(int x,int y);
void Dis_heizi(int x,int y);
 
 
#endif