#include<stdio.h>
#define MAX 8
/*
	**快速排序 
	*非递归写法 
	*/ 
void QuickSortNonR(int* a, int begin, int end)
{
	ST st;
	StackInit(&st);
	StackPush(&st, begin);
	StackPush(&st, end);
 
	while (!StackEmpty(&st))
	{
		int right = StackTop(&st);
		StackPop(&st);
		int left = StackTop(&st);
		StackPop(&st);
 
		int keyi = PartSort3(a, left, right);
		// [left,keyi-1][keyi+1，right]
		if (left < keyi - 1)
		{
			StackPush(&st, left);
			StackPush(&st, keyi - 1);
		}
 
		if (keyi + 1 < right)
		{
			StackPush(&st, keyi + 1);
			StackPush(&st, right);
		}
	}
	StackDestory(&st);
}
//快速排序
void TestQuickSort()
{
	int a[] = { 6,1,2,7,9,3,4,5,10,8};
	QuickSortNonR(a, 0, sizeof(a) / sizeof(int) - 1);
	PrintArray(a, sizeof(a) / sizeof(int));
}
int main()
{
	//快速排序
	TestQuickSort();
	return 0;
}
