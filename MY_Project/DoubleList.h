#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void MY_SIGNAL2(int signal)
{
	if(signal == SIGINT)
	{
		printf("收到信号SIGINT"); 
	}
}

void MY_SIGNAL(int signal)
{
	if(signal == SIGALRM)
	{
		printf("电脑关机"); 
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
		printf("臭傻逼");
		sleep(1); 
		//TODO
		alarm(5);
	}
	return 0;
}
