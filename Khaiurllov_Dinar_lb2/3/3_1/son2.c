#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    // Игнорирование сигнала SIGTERM
    signal(SIGTERM, SIG_IGN);
    printf("Son2 (PID=%d): Ignoring SIGTERM (will NOT terminate)\n", getpid());
    // Ожидание сигнала SIGTERM (но он игнорируется)
    while (1) sleep(1);
}
