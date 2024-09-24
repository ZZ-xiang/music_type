#include<stdio.h>
#include<stdlib.h>

//Ì°ĞÄËã·¨ 
min(int Op,int currentOp)
{
	return Op < currentOp ? Op : currentOp;
}
int main()
{
	int a,b;
	scanf("%d %d",&a,&b);
	int* flag = (int*)malloc(sizeof(int) * a);
	
	for(int i=0;i<a;i++)
	{
		scanf("%d",&flag[i]);
	}
	
	int sum = 0;
	for(int i=0;i<a;i++)
	{
		sum += flag[i];
	}
	 
	 
	int Op = 100000;
	for(int mask = 0;mask < (1<<a);mask++)
	{
		int currentSum = 0;
		int currentOp = 0;
		for(int i=0;i< a;i++)
		{
			//TODO
			if(mask & (1 << i)) //2^i 
			{
				currentSum += flag[i];
			}
			else
			{
				currentOp++;
			}
		}
		int xiaozhou = currentSum % b;
		if(xiaozhou == 0)
		{
			//TODO
			Op = min(Op,currentOp);
		}
		else
		{
			int c = b - xiaozhou;
			currentOp += c;
			Op = min(Op,currentOp);
		}
		
	} 
	
	printf("%d\n",Op);
	free(flag);
	return 0;
	
}
