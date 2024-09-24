#include<stdio.h>
int main()
{
	int a;
	int Bit = 1;
	scanf("%d",&a);
	while(a)
	{
		if(a%2 == 1)
		{
			Bit = Bit*10+1;
		}
		a/=2;
	}
	Bit = Bit/10;
	printf("%d",Bit);
	
}
