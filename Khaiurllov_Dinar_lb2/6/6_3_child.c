#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <bits/sigaction.h>

void receiver_handler(int sig_num)
{
    printf("Child [PID:%d]: Signal received %d (%s)\n",getpid(), sig_num, strsignal(sig_num));
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printf("Child: Got parameter '%s'\n", argv[1]);
    }
    
    struct sigaction sa;
    sa.sa_handler = receiver_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGUSR1, &sa, NULL))
    {
        perror("Error handler");
        return 1;
    }
    
    printf("Child [PID:%d, PPID:%d] waits for signal\n", getpid(), getppid());
    
    while (1)
    {
        pause();
    }
    
    return 0;
}
