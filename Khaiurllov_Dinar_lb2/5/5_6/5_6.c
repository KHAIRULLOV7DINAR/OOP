#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void* thread_func(void* arg)
{
    int policy;
    struct sched_param param;
    
    // Получаем параметры планирования текущего потока
    pthread_getschedparam(pthread_self(), &policy, &param);
    
    const char* policy_name;
    switch(policy)
    {
        case SCHED_OTHER: policy_name = "SCHED_OTHER"; break;
        case SCHED_FIFO:  policy_name = "SCHED_FIFO";  break;
        case SCHED_RR:    policy_name = "SCHED_RR";    break;
        default:          policy_name = "UNKNOWN";     break;
    }
    
    printf("Thread: policy = %s, priority = %d\n", policy_name, param.sched_priority);
    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    
    return 0;
}
