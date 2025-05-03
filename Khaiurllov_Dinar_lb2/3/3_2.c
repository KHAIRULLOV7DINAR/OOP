#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pids[3];

    for (int i = 0; i < 3; ++i)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            printf("Child %d: PID=%d running...\n", i+1, getpid());
            sleep(3 + i); // разная длительность
            printf("Child %d: finished\n", i+1);
            exit(i+1); // возвращаем свой номер как код
        }
    }

    // Ждём первый дочерний процесс
    int status;
    pid_t pid = waitpid(pids[0], &status, 0);
    if (pid > 0)
    {
        printf("Parent: Caught child PID=%d, ", pid);
        if (WIFEXITED(status))
        {
            printf("exit code = %d\n", WEXITSTATUS(status));
        }
    }
    // Ожидание завершения второго процесса с параллельным выполнением дополнительного кода
    while ((pid = waitpid(pids[1], &status, WNOHANG)) == 0)
    {
        printf("Parent process is doing some work \n");
        sleep(2);
    }
    printf("Parent: Caught child PID=%d, ", pids[1]);
    if (WIFEXITED(status))
    {
        printf("exit code = %d\n", WEXITSTATUS(status));
    }

    printf("Parent: done waiting for selected children. Others may still run or become zombies.\n");
    sleep(10);
    system("ps -l");
    
    //Не дожидаемся выполнения третьего процесса
    //После завершения родительского процесса третий дочерний процесс сменить родителя

    sleep(5); // даём время остальным дочерним процессам завершиться
    return 0;
}
