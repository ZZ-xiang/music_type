#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
  
// 共享资源  
int shared_data = 0;  
  
// 互斥量  
pthread_mutex_t mutex;  
  
// 线程的工作函数  
void* worker(void* arg) {  
    int i;  
    for (i = 0; i < 100000; i++) {  
        // 锁住互斥量  
        pthread_mutex_lock(&mutex);  
  
        // 修改共享资源  
        shared_data++;  
  
        // 解锁互斥量  
        pthread_mutex_unlock(&mutex);  
    }  
    return NULL;  
}  
  
int main() {  
    pthread_t thread1, thread2;  
  
    // 初始化互斥量  
    pthread_mutex_init(&mutex, NULL);  
  
    // 创建两个线程  
    pthread_create(&thread1, NULL, worker, NULL);  
    pthread_create(&thread2, NULL, worker, NULL);  
  
    // 等待两个线程结束  
    pthread_join(thread1, NULL);  
    pthread_join(thread2, NULL);  
  
    // 销毁互斥量  
    pthread_mutex_destroy(&mutex);  
  
    printf("shared_data = %d\n", shared_data);  
    return 0;  
}
