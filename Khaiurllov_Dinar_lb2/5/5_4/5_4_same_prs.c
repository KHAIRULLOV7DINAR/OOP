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

#define ITERATIONS 3
#define COMPUTATION_LOOP 500000000ULL

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
    }
}

void record_execution(int proc_id, int priority_val, int iter_num)
{
    int log_file = open("round_robin_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_file == -1)
    {
        perror("Failed to access log file");
        exit(EXIT_FAILURE);
    }

    struct timespec time_spec;
    clock_gettime(CLOCK_MONOTONIC, &time_spec);

    double time_msec = time_spec.tv_sec * 1000.0 + time_spec.tv_nsec / 1e6;

    char log_buffer[150];
    int buffer_len = snprintf(log_buffer, sizeof(log_buffer),
        "Task %d (priority %2d) - iteration %d at %.3f ms\n",
        proc_id, priority_val, iter_num, time_msec);

    write(log_file, log_buffer, buffer_len);
    close(log_file);
}

void process_work(int task_id, int task_priority)
{
    assign_cpu(0);
    setup_rr_policy(task_priority);

    for (int current_iter = 0; current_iter < ITERATIONS; current_iter++)
    {
        computation_task();
        record_execution(task_id, task_priority, current_iter+1);
    }
}

int main()
{
    if (getuid() != 0)
    {
        fprintf(stderr, "Superuser privileges required! Run with sudo.\n");
        return EXIT_FAILURE;
    }

    int log_fd = open("round_robin_log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (log_fd != -1) close(log_fd);

    pid_t child_processes[3];
    int priority_levels[3] = {30, 30, 30}; 

    for (int i = 0; i < 3; i++)
    {
        child_processes[i] = fork();
        if (child_processes[i] == 0)
        {
            setup_rr_policy(priority_levels[i]);
            process_work(i + 1, priority_levels[i]);
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

    system("cat round_robin_log.txt");
    printf("Execution completed.\n");

    return EXIT_SUCCESS;
}
