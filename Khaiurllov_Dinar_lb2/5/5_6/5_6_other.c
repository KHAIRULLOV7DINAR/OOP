#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <sys/syscall.h>
#include <stdlib.h>

#define ITERATIONS 5
#define OUTPUT_FILENAME "scheduling_output.txt"

FILE* log_file;

void* worker_thread(void* arg)
{
    int thread_id = syscall(SYS_gettid);
    for (int count = 0; count < ITERATIONS; count++)
    {
        fprintf(log_file, "OTHER thread ID: %d\n", thread_id);
        fflush(log_file); 
        usleep(1000);
    }
    return NULL;
}

int main() {
    log_file = fopen(OUTPUT_FILENAME, "w");
    if (log_file == NULL)
    {
        perror("Failed to open output file");
        return 1;
    }

    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, worker_thread, NULL);
    pthread_create(&thread2, NULL, worker_thread, NULL);
    pthread_create(&thread3, NULL, worker_thread, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    fclose(log_file);

    printf("Thread execution log:\n");
    system("cat " OUTPUT_FILENAME);
    
    return 0;
}
