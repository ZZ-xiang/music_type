#include<stdio.h>
#include<stdlib.h>

int mySqrt(int x)
{
    if(x == 1)
    {
		return 1;
	}
	if(x == 0)
	{
		return 0;
		//TODO
	}
	int left = 0;
	int right = x;
	while(right-left>1)
	{
		int m = (left + right)/2;
		if(m*m>x)

		{
			right = m; 
		}
		else
		{
			left = m;
		}
	}
	return left;
	
}

int main()
{
	printf("%d",mySqrt(28));
	
}
