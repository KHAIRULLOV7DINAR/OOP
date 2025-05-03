#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 5  // Увеличим для наглядности
#define COMPUTATION_LOOP 100000000ULL  // Уменьшим для более частого переключения

void assign_cpu(int cpu_num)
{
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(cpu_num, &cpu_set);

    if (sched_setaffinity(0, sizeof(cpu_set), &cpu_set) == -1)
    {
        perror("Failed to set CPU affinity");
        exit(EXIT_FAILURE);
    }
}

void setup_rr_policy(int priority_level)
{
    struct sched_param sched_params;
    sched_params.sched_priority = priority_level;

    if (sched_setscheduler(0, SCHED_RR, &sched_params) == -1)
    {
        perror("Failed to set scheduler policy");
        exit(EXIT_FAILURE);
    }
}

void computation_task()
{
    volatile unsigned long long computation_var = 0;
    for (unsigned long long i = 0; i < COMPUTATION_LOOP; i++)
    {
        computation_var++;
        if (i % 10000000 == 0)  // Добавляем точки yield
        {
            sched_yield();
        }
    }
}

void record_execution(int proc_id, int iter_num)
{
    int log_file = open("rr_yield_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_file == -1)
    {
        perror("Failed to access log file");
        exit(EXIT_FAILURE);
    }

    struct timespec time_spec;
    clock_gettime(CLOCK_MONOTONIC, &time_spec);

    char log_buffer[100];
    int buffer_len = snprintf(log_buffer, sizeof(log_buffer),
        "Task %d - iteration %d at %ld.%09ld sec\n",
        proc_id, iter_num, time_spec.tv_sec, time_spec.tv_nsec);

    write(log_file, log_buffer, buffer_len);
    close(log_file);
}

void process_work(int task_id)
{
    assign_cpu(0);
    
    for (int current_iter = 0; current_iter < ITERATIONS; current_iter++)
    {
        computation_task();
        record_execution(task_id, current_iter+1);
        sched_yield();  // Явное освобождение процессора после каждой итерации
    }
}

int main()
{
    if (getuid() != 0)
    {
        fprintf(stderr, "Superuser privileges required! Run with sudo.\n");
        return EXIT_FAILURE;
    }

    int log_fd = open("rr_yield_log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (log_fd != -1) close(log_fd);

    pid_t child_processes[3];
    int priority_levels[3] = {30, 30, 30};  // Одинаковые приоритеты

    for (int i = 0; i < 3; i++)
    {
        child_processes[i] = fork();
        if (child_processes[i] == 0)
        {
            setup_rr_policy(priority_levels[i]);
            process_work(i + 1);
            exit(EXIT_SUCCESS);
        }
        else if (child_processes[i] < 0)
        {
            perror("Failed to create process");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        waitpid(child_processes[i], NULL, 0);
    }

    system("cat rr_yield_log.txt");
    printf("Execution completed.\n");

    return EXIT_SUCCESS;
}
