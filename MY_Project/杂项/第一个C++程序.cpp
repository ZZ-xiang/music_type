#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
int  main()
{
	float x;
	int a,b;
	scanf_s("%d %d",&a,&b);
	x = (float)(sqrt(abs(a-b)) / (3*(a+b)));
	printf("%.16f",x);

	return 0;
}
