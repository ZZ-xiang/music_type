#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
  
// ������Դ  
int shared_data = 0;  
  
// ������  
pthread_mutex_t mutex;  
  
// �̵߳Ĺ�������  
void* worker(void* arg) {  
    int i;  
    for (i = 0; i < 100000; i++) {  
        // ��ס������  
        pthread_mutex_lock(&mutex);  
  
        // �޸Ĺ�����Դ  
        shared_data++;  
  
        // ����������  
        pthread_mutex_unlock(&mutex);  
    }  
    return NULL;  
}  
  
int main() {  
    pthread_t thread1, thread2;  
  
    // ��ʼ��������  
    pthread_mutex_init(&mutex, NULL);  
  
    // ���������߳�  
    pthread_create(&thread1, NULL, worker, NULL);  
    pthread_create(&thread2, NULL, worker, NULL);  
  
    // �ȴ������߳̽���  
    pthread_join(thread1, NULL);  
    pthread_join(thread2, NULL);  
  
    // ���ٻ�����  
    pthread_mutex_destroy(&mutex);  
  
    printf("shared_data = %d\n", shared_data);  
    return 0;  
}
