#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Child started (PID=%d, PPID=%d)\n", getpid(), getppid());
    sleep(2);  // Имитация работы
    printf("Child finished (PID=%d)\n", getpid());
    return 0;
}
