#include<stdio.h>
#define MAX 8 
/*
	**��������ÿ��ѡ����������ǰ������ԱȲ������±�++ 
	*/ 
int main()
{
	 int arr[MAX] = {1,6,3,5,1,3,6,7};
	 for(int i=0;i<MAX;i++)
	 {
	 	int temp = arr[i];
	 	int j = i-1;
	 	while(j >= 0 && arr[j] > temp)
		{
		 	//TODO
		 	arr[j+1] = arr[j];
		 	j--;
		}
		arr[j+1] = temp;
	 }
	 
	 for(int i=0;i<MAX;i++){
	 	//TODO
	 	printf("%d",arr[i]);
	 	
	 }
}
