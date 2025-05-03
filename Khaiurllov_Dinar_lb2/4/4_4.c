#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>

typedef struct
{
    int thread_num;
    pid_t tid;
} thread_data;

void* thread_function(void* arg)
{
    thread_data* data = (thread_data*)arg;
    data->tid = syscall(SYS_gettid);
    
    printf("Thread %d appeared (TID: %d)\n", data->thread_num, data->tid);
    
    while(1)
    {
        printf("Thread %d (TID: %d) working...\n", data->thread_num, data->tid);
        sleep(2);
    }
    
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    thread_data data1 = {1, 0};
    thread_data data2 = {2, 0};
    
    printf("Main process (PID: %d)\n", getpid());
    
    // Создаем две нити
    pthread_create(&thread1, NULL, thread_function, &data1);
    pthread_create(&thread2, NULL, thread_function, &data2);
    
    // Даем потокам время установить свои TID
    sleep(1);
    
    printf("Trying to kill thread 2 with TID: %d\n", data2.tid);
    
    // Пытаемся убить поток
    if(kill(data2.tid, SIGKILL) == -1)
    {
        perror("Error kill");
    }
    
    // Ждем некоторое время для наблюдения
    sleep(5);
    
    return 0;
}
