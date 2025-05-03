#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <string.h>

#define ITERATION_COUNT 5
#define COMPUTATION_CYCLES 100000000ULL

void bind_to_processor(int core_num)
{
    cpu_set_t core_mask;
    CPU_ZERO(&core_mask);
    CPU_SET(core_num, &core_mask);
    
    if (sched_setaffinity(0, sizeof(core_mask), &core_mask) != 0)
    {
        perror("Failed to set CPU affinity");
        exit(EXIT_FAILURE);
    }
}

void perform_computations()
{
    volatile unsigned long long counter = 0;
    for (unsigned long long i = 0; i < COMPUTATION_CYCLES; i++)
    {
        counter++;
    }
}

void log_execution(const char *scheduling_policy, int cycle_num, int process_id)
{
    int log_fd = open("scheduling_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1)
    {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    double timestamp = current_time.tv_sec * 1000.0 + current_time.tv_nsec / 1e6;

    char log_entry[200];
    int entry_length = snprintf(log_entry, sizeof(log_entry),
        "[%8.3f ms] Process %d (%s) - iteration %d\n", 
        timestamp, process_id, scheduling_policy, cycle_num);
    
    write(log_fd, log_entry, entry_length);
    close(log_fd);
}

void execute_task(const char *policy_name, int policy_type, int priority_level)
{
    bind_to_processor(0);

    if (policy_type != SCHED_OTHER)
    {
        struct sched_param scheduler_params = { .sched_priority = priority_level };
        if (sched_setscheduler(0, policy_type, &scheduler_params) == -1)
        {
            perror("Failed to configure scheduler");
            exit(EXIT_FAILURE);
        }
    }

    for (int current_cycle = 1; current_cycle <= ITERATION_COUNT; current_cycle++)
    {
        perform_computations();
        log_execution(policy_name, current_cycle, getpid());
        sched_yield();
    }
    exit(EXIT_SUCCESS);
}

int main()
{
    if (getuid() != 0)
    {
        fprintf(stderr, "Superuser privileges required! Run with sudo.\n");
        return EXIT_FAILURE;
    }

    int log_file = open("scheduling_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (log_file != -1) close(log_file);

    pid_t process_ids[2];

    process_ids[0] = fork();
    if (process_ids[0] == 0) execute_task("SCHED_RR", SCHED_RR, 15);

    process_ids[1] = fork();
    if (process_ids[1] == 0) execute_task("SCHED_FIFO", SCHED_FIFO, 15);

    for (int i = 0; i < 2; i++)
    {
        waitpid(process_ids[i], NULL, 0);
    }

    system("cat scheduling_log.txt");
    printf("Test completed.\n");

    return EXIT_SUCCESS;
}
