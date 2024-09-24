#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

struct task {
    void *(*do_task)(void *arg); // ����ָ�룬ָ������Ҫִ�еĺ�������������
    void *arg; // һ��ָ�룬����ִ�к���ʱ��Ϊ�����Ĳ������루����������Ҫ��������ݣ�
    struct task *next;
};

typedef struct thread_pool {
    pthread_mutex_t lock; // �������������������"�̳߳�"�����Ǳ�����������
    pthread_cond_t cond; // �����������
    bool shutdown; // ��������̳߳��Ƿ��˳��� true�Ѿ�Ҫ�ػ� false���ػ�
    struct task *task_list; // ����������ָ���һ��������
    pthread_t *tids; // ָ���߳�ID�����飬��Ϊ�ҿ��ܻᴴ������̡߳�
    unsigned max_waiting_tasks; // ��ʾ����ִ�е�������(����ڵ�����)
    unsigned waiting_tasks; // Ŀǰ���������ϵ�������������ִ�����񣨵�ǰ����ڵ������
    unsigned active_threads; // ���ڷ��۵��߳�������ǰ�����ߵ�������
} thread_pool;

bool init_pool(thread_pool *pool, unsigned int threads_number);
bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *task);
int add_thread(thread_pool *pool, unsigned int additional_threads_number);
int remove_thread(thread_pool *pool, unsigned int removing_threads_number);
bool destroy_pool(thread_pool *pool);
void *routine(void *arg); // ����ִ�к������̺߳���)

bool init_pool(thread_pool *pool, unsigned int threads_number) {
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);
    pool->shutdown = false;
    pool->task_list = NULL;
    pool->max_waiting_tasks = 20;
    pool->waiting_tasks = 0;
    pool->active_threads = threads_number;
    pool->tids = (pthread_t *)malloc(sizeof(pthread_t) * threads_number);
    if (pool->tids == NULL) {
        perror("malloc");
        return false;
    }
    for (unsigned int i = 0; i < threads_number; ++i) {
        if (pthread_create(&pool->tids[i], NULL, routine, (void *)pool) != 0) {
            perror("pthread_create");
            return false;
        }
    }
    return true;
}

bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *task) {
    struct task *new_task = (struct task *)malloc(sizeof(struct task));
    if (new_task == NULL) {
        perror("malloc");
        return false;
    }
    new_task->do_task = do_task;
    new_task->arg = task;
    new_task->next = NULL;

    pthread_mutex_lock(&pool->lock); //��ס 
    if (pool->waiting_tasks >= pool->max_waiting_tasks) {
        pthread_mutex_unlock(&pool->lock);
        free(new_task);
        return false;
    }
    if (pool->task_list == NULL) {
        pool->task_list = new_task;
    } else {
        struct task* temp = pool->task_list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_task;
    }
    pool->waiting_tasks++;
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->lock);
    return true;
}

int add_thread(thread_pool *pool, unsigned int additional_threads_number) {
    if (pool->active_threads + additional_threads_number > 20) {
        return -1;
    }
    pool->tids = (pthread_t *)realloc(pool->tids, sizeof(pthread_t) * (pool->active_threads + additional_threads_number));
    if (pool->tids == NULL) {
        perror("realloc");
        return -1;
    }
    for (unsigned int i = pool->active_threads; i < pool->active_threads + additional_threads_number; ++i) {
        if (pthread_create(&pool->tids[i], NULL, routine, (void *)pool) != 0) {
            perror("pthread_create");
            return -1;
        }
    }
    pool->active_threads += additional_threads_number;
    return 0;
}

int remove_thread(thread_pool *pool, unsigned int removing_threads_number) {
    if (pool->active_threads - removing_threads_number < 1) {
        return -1;
    }
    for (unsigned int i = pool->active_threads - removing_threads_number; i < pool->active_threads; ++i) {
        pthread_cancel(pool->tids[i]);
        pthread_join(pool->tids[i], NULL);
    }
    pool->active_threads -= removing_threads_number;
    return 0;
}

bool destroy_pool(thread_pool *pool) {
    pool->shutdown = true;
    pthread_cond_broadcast(&pool->cond);
    for (unsigned int i = 0; i < pool->active_threads; ++i) {
        pthread_join(pool->tids[i], NULL);
    }
    free(pool->tids);
    struct task *temp;
    while (pool->task_list != NULL) {
        temp = pool->task_list;
        pool->task_list = pool->task_list->next;
        free(temp);
    }
    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cond);
    return true;
}

void *routine(void *arg) {
    thread_pool *pool = (thread_pool *)arg;
    while (1) {
        pthread_mutex_lock(&pool->lock);
        while (pool->waiting_tasks == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->cond, &pool->lock);
        }
        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->lock);
            pthread_exit(NULL);
        }
        struct task *pnow = pool->task_list;
        pool->task_list = pool->task_list->next;
        pool->waiting_tasks--;
        pthread_mutex_unlock(&pool->lock);
        pnow->do_task(pnow->arg);
        free(pnow);
    }
    return NULL;
}

void *example_task(void *arg) {
    int *num = (int *)arg;
    printf("Thread %ld is working on task %d\n", pthread_self(), *num);
    sleep(1);
    return NULL;
}

int main() {
    thread_pool pool;
    init_pool(&pool, 2);
    
    for (int i = 0; i < 10; ++i) {
        int *task = (int *)malloc(sizeof(int));
        *task = i;
        add_task(&pool, example_task, task);
        
        // ��̬�����߳�����
        pthread_mutex_lock(&pool.lock);
        if (pool.waiting_tasks > pool.active_threads * 2) {
            add_thread(&pool, 1);
        } else if (pool.waiting_tasks < pool.active_threads && pool.active_threads > 2) {
            remove_thread(&pool, 1);
        }
        pthread_mutex_unlock(&pool.lock);
    }

    sleep(5);
    destroy_pool(&pool);
    return 0;
}
