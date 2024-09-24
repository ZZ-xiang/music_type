#include<stdio.h>
#define MAX 8
/*
	**快速排序 
	*递归写法
	*思路：
	*	  ①设置要排序的一个数，然后设置递归，层层递进（起点++，终点--），直到起点>终点
	*	  ②设置一个函数对排序得数进行排序 --> 	
	*											①设置标志位，选取要排序的数，此代码中选取的未遍历的最后一位
	*											②将比标志位小的数全部安排在左边，利用swap函数交换
	*											③排完最后将空缺位置与最后一个数交换位置
	*	  ③结束 
	*/ 
void QuickSort(int arr[],int start,int polite);
int realize(int arr[],int start,int polite);
void swap(int* a,int *b);

int main()
{
	int arr[MAX] = {10,6,3,50,1,3,6,7};
	QuickSort(arr,0,MAX-1); 
	for(int i=0;i<MAX;i++){
		//TODO
		printf("%d ",arr[i]);
	} 
}

void QuickSort(int arr[],int start,int polite)
{
	if(start < polite)
	{
		realize(arr,start,polite);
		QuickSort(arr,start+1,polite);
		QuickSort(arr,start,polite-1);
	}
}

int realize(int arr[],int start,int polite)
{
	//flag:用来标志快排的数 
	int flag = arr[polite];
	int low = start;
	for(int i=low;i<polite;i++)
	{
		if(arr[i] < flag)
		{
			swap(&arr[i],&arr[low++]);
		}
	}
	swap(&arr[polite],&arr[low]);
	return low;
}

void swap(int* a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
