#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void MY_SIGNAL2(int signal)
{
	if(signal == SIGINT)
	{
		printf("�յ��ź�SIGINT"); 
	}
}

void MY_SIGNAL(int signal)
{
	if(signal == SIGALRM)
	{
		printf("���Թػ�"); 
		//TODO
	}
}

int main()
{
    printf("sss");
	signal(SIGALRM,MY_SIGNAL);
	signal(SIGINT,MY_SIGNAL2);
	alarm(5);
	while(1)
	{
		printf("��ɵ��");
		sleep(1); 
		//TODO
		alarm(5);
	}
	return 0;
}
