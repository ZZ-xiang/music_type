#include<stdio.h>
#define MAX 8
int main()
{	
/*
	**希尔排序 利用分治法(分而治之)
	*/ 
	int arr[MAX] = {1,6,3,5,1,3,6,7};
	for(int i=MAX/2;i>0;i /= 2)
	{
		//利用类插入排序 
		for(int j = i;j<MAX;j++)
		{
			int temp = arr[j];
			int k;
			for(k = j;k>=i && arr[k-i] >= temp;k-=i)
			{
				arr[k] = arr[k-i];
			}
			arr[k] = temp;
		} 
	}
	
	for(int i=0;i<MAX;i++){
		//TODO
		printf("%d",arr[i]);
	}
}
