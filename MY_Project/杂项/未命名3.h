#include<stdio.h>
#define N 2
#define M 3

int select(int a[N][M],int *row,int *col)
{
	for(int i = 0;i<N;i++)
	{
		for(int j = 1;j<M;j++)
		{
			if(a[i][j]>a[i][j-1])
			{
				*row = i;
				*col = j;
			}
		} 
	}
	return 0;
}

int main()
{
	int row,col;
	int a[2][3] = {{1,2,3},{4,5,6}};
	select(a,&row,&col);
	printf("%d,%d",row,col);
	
}
