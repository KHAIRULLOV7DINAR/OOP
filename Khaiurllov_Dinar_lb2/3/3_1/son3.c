#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    printf("Son3 (PID=%d): Custom SIGTERM handler (signal %d)\n", getpid(), sig);
    // Завершаем процесс после обработки
    exit(0);  
}

int main()
{
    // Установка своего обработчика сигнала
    signal(SIGTERM, handler);
    printf("Son3 (PID=%d): Custom SIGTERM handler installed\n", getpid());
    // Ожидание сигнала
    while (1) sleep(1); 
}
