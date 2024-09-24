#include<stdio.h>
#define MAX 8 
/*
	**选择排序 每次选择后续最大/最小的排序 
	*/ 
int main()
{	
	int arr[MAX] = {10,6,3,50,1,3,6,7};
	int min_flag = 0;
	for(int i=0;i<MAX-1;i++)
	{
		for(int j=i;j<MAX;j++)
		{
			if(arr[j] < arr[min_flag])
			{
				min_flag = j;
			}
		}
		
		int temp = 0;
		temp = arr[min_flag];
		arr[min_flag] = arr[i];
		arr[i] = temp;
		
	}

	for(int i=0;i<MAX;i++)
	{
		printf("%d ",arr[i]);
	}
}
