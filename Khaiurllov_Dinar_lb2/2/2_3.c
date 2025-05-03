#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void wait_child()
{
    if (wait(NULL) == -1)
    {
        perror("wait error");
        exit(EXIT_FAILURE);
    }
}

void run_execle()
{
    printf("\n[execle] Running /usr/bin/env with new environment via execle...\n");
    // Новая переменная окружения для дочернего процесса
    char *envp[] = {"MYVAR=ChildValue", NULL};
    execle("/usr/bin/env", "env", NULL, envp);
    
    //Обработка ошибки
    perror("execle error");
    exit(EXIT_FAILURE);
}

void run_execlp()
{
    printf("\n[execlp] Running echo via execlp (PATH search)...\n");
    execlp("echo", "echo", "Message", "via", "execlp", NULL);
    
    //Обработка ошибки
    perror("execlp error");
    exit(EXIT_FAILURE);
}

void run_execvp()
{
    printf("\n[execvp] Running sh with env command via execvp...\n");
    char *argv[] = {"sh", "-c", "env | grep MYVAR", NULL};  // Проверка переменной окружения
    execvp("sh", argv);
    
    //Обработка ошибки
    perror("execlp error");
    exit(EXIT_FAILURE);
}

void run_execve()
{
    printf("\n[execve] Running /usr/bin/env with arguments and environment via execve...\n");
    char *args[] = {"/usr/bin/env", NULL};
    char *envp[] = {"MYVAR=ChildValue", "HOME=/tmp", NULL};  // Передаем новое окружение
    execve("/usr/bin/env", args, envp);
    
    //Обработка ошибки
    perror("execlp error");
    exit(EXIT_FAILURE);
}

int main()
{
    setenv("MYVAR", "ParentValue", 1);  // Устанавливаем переменную окружения для родителя
    printf("Parent: PID=%d, MYVAR=%s\n", getpid(), getenv("MYVAR"));

    // Запуск с execle
    if (fork() == 0)
    {
        run_execle();
    }
    wait_child();

    // Запуск с execlp
    if (fork() == 0)
    {
        run_execlp();
    }
    wait_child();

    // Запуск с execvp для проверки переменной окружения MYVAR
    if (fork() == 0)
    {
        run_execvp();
    }
    wait_child();

    // Запуск с execve
    if (fork() == 0)
    {
        run_execve();
    }
    wait_child();

    printf("Parent: PID=%d finished\n", getpid());
    return EXIT_SUCCESS;
}
