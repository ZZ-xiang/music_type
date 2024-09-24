// #include <stdio.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <stdlib.h>

// void* func1(void* arg)
// {
// 	while(1)
// 	{
// 		printf("hahahahaha\n");
// 		system("madplay Music.mp3");
// 		sleep(4);
// 	}
// }

// int func2(void)
// {
// 	while(1)
// 	{
// 		printf("xixixixixi\n");
// 		sleep(4);
// 	}
// }

// int main(void)
// {
// 	pthread_t tid = 0;
	
// 	if(pthread_create(&tid,NULL,func1,NULL))	/* 创建一个执行分支（线程）去执行func1 */
// 	{  
// 		perror("pthread_create error");
// 		return -1;
// 	}

// 	//func1();
// 	func2();
// }

