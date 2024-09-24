#include<stdio.h>
#define MAX 8
/*
	**�������� 
	*�ݹ�д��
	*˼·��
	*	  ������Ҫ�����һ������Ȼ�����õݹ飬���ݽ������++���յ�--����ֱ�����>�յ�
	*	  ������һ����������������������� --> 	
	*											�����ñ�־λ��ѡȡҪ����������˴�����ѡȡ��δ���������һλ
	*											�ڽ��ȱ�־λС����ȫ����������ߣ�����swap��������
	*											��������󽫿�ȱλ�������һ��������λ��
	*	  �۽��� 
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
	//flag:������־���ŵ��� 
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
