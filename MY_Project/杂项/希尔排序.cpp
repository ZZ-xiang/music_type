#include<stdio.h>
#define MAX 8
int main()
{	
/*
	**ϣ������ ���÷��η�(�ֶ���֮)
	*/ 
	int arr[MAX] = {1,6,3,5,1,3,6,7};
	for(int i=MAX/2;i>0;i /= 2)
	{
		//������������� 
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
