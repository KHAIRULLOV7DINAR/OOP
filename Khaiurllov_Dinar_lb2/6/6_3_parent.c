#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <bits/sigaction.h>

#define MAX_SIGNALS 5

typedef struct
{
    int signal_count;
    int received_signals[MAX_SIGNALS];
} SignalTracker;

void custom_signal_handler(int sig_num)
{
    static int counter = 0;
    printf("Signal received: %d (%s)\n", 
           sig_num, strsignal(sig_num));
    counter++;
}

void setup_signal_handling()
{
    struct sigaction sa;
    sa.sa_handler = custom_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGUSR1, &sa, NULL))
    {
        perror("Error signal handler");
        exit(EXIT_FAILURE);
    }
}

void child_process_operations()
{
    printf("Child process [PID:%d]: Sending SIGUSR1 to exec\n", getpid());
    if (kill(getpid(), SIGUSR1))
    {
        perror("Error signal send");
    }
    
    char *args[] = {"./6_3_child.out", "custom_param", NULL};
    if (execv(args[0], args))
    {
        perror("Error execv");
        exit(EXIT_FAILURE);
    }
}

void parent_process_operations(pid_t child_pid)
{
    sleep(1);
    
    printf("\nParent process [PID:%d]:\n", getpid());
    printf("1. Sending SIGUSR1 to self\n");
    raise(SIGUSR1);
    
    printf("2. Sending SIGUSR1 to child process [PID:%d]\n", child_pid);
    if (kill(child_pid, SIGUSR1))
    {
        perror("Error sending signal to chlid process");
    }
    
    int status;
    waitpid(child_pid, &status, 0);
    printf("Child process ended: %d\n", WEXITSTATUS(status));
}

int main()
{
    setup_signal_handling();
    
    pid_t child_pid = fork();
    switch (child_pid)
    {
        case -1:
            perror("Error process creation");
            return EXIT_FAILURE;
        case 0:
            child_process_operations();
            break;
        default:
            parent_process_operations(child_pid);
    }
    
    return EXIT_SUCCESS;
}
