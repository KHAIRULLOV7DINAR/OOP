#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define ITER_COUNT 3
#define COMPUTE_CYCLES 500000000ULL

// Приоритеты для каждого из трех процессов
const int PRIORITIES[3] = {10, 55, 50}; 

void bind_to_core(int core)
{
    cpu_set_t core_mask;
    CPU_ZERO(&core_mask);
    CPU_SET(core, &core_mask);

    if (sched_setaffinity(0, sizeof(core_mask), &core_mask) == -1)
    {
        perror("Failed to set CPU affinity");
        exit(EXIT_FAILURE);
    }
}

void configure_scheduler(int prio)
{
    struct sched_param sp;
    sp.sched_priority = prio;

    if (sched_setscheduler(0, SCHED_FIFO, &sp) == -1)
    {
        perror("Failed to set scheduler");
        exit(EXIT_FAILURE);
    }
}

void perform_computation()
{
    volatile unsigned long long counter = 0;
    for (unsigned long long i = 0; i < COMPUTE_CYCLES; i++)
    {
        counter++;
    }
}

void log_progress(int proc_num, int iter, int priority)
{
    int log_fd = open("scheduler_log.txt", O_WRONLY|O_CREAT|O_APPEND, 0644);
    if (log_fd == -1)
    {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }

    char log_entry[100];
    int entry_len = snprintf(log_entry, sizeof(log_entry),
                         "Process %d (priority %d) completed iteration %d\n",
                         proc_num, priority, iter);
    write(log_fd, log_entry, entry_len);
    close(log_fd);
}

void execute_task(int task_id)
{
    bind_to_core(0);
    configure_scheduler(PRIORITIES[task_id-1]); // Используем разные приоритеты

    for (int cycle = 0; cycle < ITER_COUNT; cycle++)
    {
        perform_computation();
        log_progress(task_id, cycle+1, PRIORITIES[task_id-1]);
    }
}

int main()
{
    if (getuid() != 0)
    {
        fprintf(stderr, "Superuser privileges required! Run with sudo.\n");
        return EXIT_FAILURE;
    }

    // Создаем лог-файл
    int log_fd = open("scheduler_log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (log_fd != -1) close(log_fd);

    pid_t child_pids[3];

    for (int i = 0; i < 3; i++)
    {
        child_pids[i] = fork();
        if (child_pids[i] == 0)
        {
            execute_task(i + 1);
            exit(EXIT_SUCCESS);
        }
        else if (child_pids[i] < 0)
        {
            perror("Failed to create process");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        waitpid(child_pids[i], NULL, 0);
    }

    system("cat scheduler_log.txt");
    printf("Execution completed.\n");

    return EXIT_SUCCESS;
}
