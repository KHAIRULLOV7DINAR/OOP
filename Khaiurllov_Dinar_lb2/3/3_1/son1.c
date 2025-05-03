#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Son1 (PID=%d): Default SIGTERM handler (will terminate)\n", getpid());
    // Ожидание сигнала
    while (1) sleep(1); 
}
