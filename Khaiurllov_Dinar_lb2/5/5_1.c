#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void child_process(int id)
{
        printf(
        "Child: %d | PID: %d | PPID: %d\n", 
        id,
        getpid(), 
        getppid()
        );
    for (int i = 0; i < 15; i++)
    {
        printf("%d", id);
        fflush(stdout);
        sleep(1);
    }
    exit(0);
}

int main()
{
    pid_t pid1 = fork();
    if (pid1 == 0) { child_process(1); return 0; }

    pid_t pid2 = fork();
    if (pid2 == 0) { child_process(2); return 0; }

    wait(NULL); wait(NULL);
    printf("\n");
    return 0;
}
