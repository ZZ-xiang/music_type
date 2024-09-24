#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SUM(a, b) a+b

int sub(int a, int b)
{
    return a-b;
}
main()
{
    int a = 3;
    printf("%d\n\n", SUM(5, 3) * 8);
    printf("%x\n", sub(++a, ++a));
}
