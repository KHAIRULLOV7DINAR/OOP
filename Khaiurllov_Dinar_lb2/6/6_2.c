#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CUSTOM_PRIORITY 35
#define POLICY SCHED_FIFO

typedef struct
{
    pid_t pid;
    int policy;
    int priority;
} ProcessInfo;

void configure_process_scheduling(int priority, int policy)
{
    struct sched_param sp = {.sched_priority = priority};
    if (sched_setscheduler(0, policy, &sp) == -1)
    {
        perror("Failed to set scheduling parameters");
        exit(EXIT_FAILURE);
    }
}

void print_process_info(const char* role)
{
    ProcessInfo info;
    struct sched_param sp;

    info.pid = getpid();
    info.policy = sched_getscheduler(0);
    
    if (sched_getparam(0, &sp) == -1)
    {
        perror("Failed to set scheduling parameters");
        exit(EXIT_FAILURE);
    }
    info.priority = sp.sched_priority;

    printf("%s process info:\n", role);
    printf("  PID: %d\n", info.pid);
    printf("  policy planning: %d (%s)\n", 
           info.policy, 
           info.policy == SCHED_FIFO ? "FIFO" : 
           info.policy == SCHED_RR ? "RR" : "OTHER");
    printf("  Приоритет: %d\n\n", info.priority);
}

int main()
{
    // Настройка параметров планирования для родительского процесса
    configure_process_scheduling(CUSTOM_PRIORITY, POLICY);

    pid_t child_pid = fork();
    switch (child_pid)
    {
        case -1:
            perror("Couldn't create a process");
            return EXIT_FAILURE;
            
        case 0:  // Дочерний процесс
            print_process_info("Child process");
            break;
            
        default:  // Родительский процесс
            print_process_info("Parent process");
            waitpid(child_pid, NULL, 0);  // Ожидание завершения дочернего процесса
            break;
    }

    return EXIT_SUCCESS;
}
