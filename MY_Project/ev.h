#ifndef __EV_H__
#define __EV_H__
 
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <linux/input.h>
 
int Get_ev(int *x,int *y);
int jud(int a,int b,int c);
 
#endif