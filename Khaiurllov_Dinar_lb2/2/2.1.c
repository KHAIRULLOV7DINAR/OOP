#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int shared_var = 100;
    // Создаём процесс-потомок
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {// Код потомка
        //Однократное вычисление
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
        shared_var += 50;
        printf("Child modified shared_var = %d\n", shared_var);
        sleep(1); // Имитация вычислений

        // Цикл для демонстрации конкуренции процессов за процессорный ресурс.
        for (int i = 0; i < 5; i++)
        {
            printf("Child working... (%d)\n", i);
            sleep(1);  // Имитация вычислений
        }
        printf("Child finished working\n");
        exit(0);  // Завершаем процесс-потомок
    } 
    else
    {  // Код родителя
        //Однократное вычисление
        printf("Parent Process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(1);
        printf("Parent's unmodified shared_var = %d\n", shared_var);
        // Цикл для демонстрации конкуренции процессов за процессорный ресурс.
        for (int i = 0; i < 5; i++)
        {
            printf("Parent working... (%d)\n", i);
            sleep(1);  // Имитация вычислений
        }

        wait(NULL);  // Ждём завершения потомка
        printf("Parent received child finish signal. Parent finished.\n");
    }

    printf("Program finished (PID=%d).\n", getpid());
    return 0;
}
