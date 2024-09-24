#include<stdio.h>
#define MAX 8
/*
	**Ã°ÅÝÅÅÐò£º±©Á¦½»»» Ê±¼ä¸´ÔÓ¶ÈO£¨n^2£© 
	*/ 
int main()
{
	int arr[MAX] = {1,6,3,5,1,3,6,7};
	for(int i=MAX-1;i>0;i--)
	{
		for(int j=0;j<i;j++)
		{
			if(arr[j] < arr[j+1])
			{
				int temp = 0;
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		
		}
	}
	for(int i=0;i<MAX-1;i++){
		//TODO
		printf("%d",arr[i]);
	} 
}
