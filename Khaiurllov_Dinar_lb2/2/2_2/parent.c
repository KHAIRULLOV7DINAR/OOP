#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Parent started (PID=%d, PPID=%d)\n", getpid(), getppid());

    // Запись состояния процессов до fork()
    system("ps -l >> log_parent_before.txt");

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {  // Потомок
        // Запуск исполняемого файла child
        execl("./child", "child", NULL);
        perror("execl failed");  // Если execl не сработал
        exit(1);
    }
    else
    {  // Родитель
        // Запись состояния процессов после fork()
        system("ps -l >> log_parent_after.txt");

        wait(NULL);  // Ждём завершения потомка
        printf("Parent finished (PID=%d)\n", getpid());
    }

    return 0;
}
