#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>

#define RESULT_F "thread_data.txt"

pthread_barrier_t sync_point;
FILE* data_fd;
pthread_mutex_t file_lock = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* param)
{
    const char* name = (const char*)param;

    pthread_barrier_wait(&sync_point);

    pthread_mutex_lock(&file_lock);
    fprintf(data_fd, "(%s) started work\n", name);
    pthread_mutex_unlock(&file_lock);

    int sched_type;
    struct sched_param sched_val;
    pthread_getschedparam(pthread_self(), &sched_type, &sched_val);

    volatile unsigned long long counter = 0;
    for (unsigned long long i = 0; i < 100000000ULL; i++)
    {
        counter++;
    }

    pthread_mutex_lock(&file_lock);
    fprintf(data_fd, "(%s) finished work\n", name);
    pthread_mutex_unlock(&file_lock);

    return NULL;
}

void setup_scheduler(pthread_t thread_id, int sched_policy, int priority)
{
    struct sched_param config;
    config.sched_priority = priority;

    if (pthread_setschedparam(thread_id, sched_policy, &config) != 0)
    {
        perror("Failed to configure scheduler");
    }
}

int main()
{
    pthread_t thread_a, thread_b;

    data_fd = fopen(RESULT_F, "w");
    if (!data_fd)
    {
        perror("Failed to open file");
        return 1;
    }

    pthread_barrier_init(&sync_point, NULL, 2);

    pthread_create(&thread_a, NULL, thread_func, (void*)"FIFO (50)");
    pthread_create(&thread_b, NULL, thread_func, (void*)"FIFO (75)");

    setup_scheduler(thread_a, SCHED_FIFO, 50);
    setup_scheduler(thread_b, SCHED_FIFO, 75);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    fprintf(data_fd, "All threads completed\n");
    fclose(data_fd);

    system("cat " RESULT_F);

    return 0;
}
