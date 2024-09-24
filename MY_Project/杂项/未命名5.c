#include<stdio.h>
charu(int arr[],int num)
{
	for(int i=1;i<num;i++)
	{	
		int j = i-1;
		int temp = arr[i];
		while(j>=0 && arr[j] < temp)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = temp;
	}
		
//	for(int i=0;i<num;i++){
//		//TODO
//		printf("%d ",arr[i]);
//	}
//	
}

xuanze(int arr[],int num)
{
	int temp = 0;
	for(int i=1;i<num;i++)
	{
		int max = i;
		for(int j=i+1;j<num;j++)
		{
			//TODO
			if(arr[j]>arr[max])
					{
						max = j;
					}
		}
		temp = arr[max];
		arr[max] = arr[i];
		arr[i] = temp;
	}
	
	for(int i=0;i<num;i++){
			//TODO
			printf("%d ",arr[i]);
		}
	
}

QuickSort(int arr[],int L,int R)
{
	int left = L;
	int right = R;
	int flag = arr[left]; //设置标志位 
	if(L>R){
		return 0;
	}
	while(left<right)
	{
		while(arr[right] > flag)
		{
			right--;
		}
		if(left < right)
		{
			arr[left] = arr[right];
		}
		while(arr[left]<= flag)
		{
			left++;
		}
		if(left < right)
		{
			arr[right] = arr[left];
		}
		if(left >= right)
		{
			arr[left] = flag;
		}
	}
	QuickSort(arr,L,right-1);
	QuickSort(arr,right+1,R);
	
	for(int i=0;i<=R;i++)
	{
		//TODO
		printf("%d",arr[i]);
	}
}
int main()
{
	 int arr[7] = {11,2,7,4,2,4,8};
//	 charu(arr,7);
//	 xuanze(arr,7);
	 QuickSort(arr,0,6);
}
