#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void log_ps(const char *label)
{
    printf("\n--- %s ---\n", label);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "echo '\n--- %s ---' >> scenarios.txt", label);
    system(cmd);
    system("ps -l | tee -a scenarios.txt");
    sleep(4);
}

int main(void)
{
    system("> scenarios.txt");

    // --- Сценарий A: Родитель ждёт завершения ---
    printf("Scenario A: Parent waits for child\n");
    pid_t pidA = fork();
    if (pidA == 0)
    {
        printf("Child A: PID=%d, PPID=%d. Working...\n", getpid(), getppid());
        sleep(4);
        printf("Child A: Finished.\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Parent A: Waiting for child A (PID=%d)...\n", pidA);
        
        log_ps("Scenario A: Before normal completion");
        waitpid(pidA, NULL, 0);
        
        printf("Parent A: Child A finished.\n");
        log_ps("Scenario A: Normal completion (child waited)");
    }

    // --- Сценарий Б: Родитель уходит до завершения потомка ---
    printf("\nScenario B: Parent exits before child\n");
    pid_t pidB = fork();
    if (pidB == 0)
    {
        pid_t orphan_pid = fork();
        if (orphan_pid == 0)
        {
            printf("Child B: PID=%d, initial PPID=%d. Sleeping...\n", getpid(), getppid());
            sleep(5);
            printf("Child B: Woke up. New PPID=%d\n", getppid());
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Parent B (intermediate): PID=%d. Created child (PID=%d), exiting...\n", getpid(), orphan_pid);
            exit(EXIT_SUCCESS);
        }
    }
    else
    {
        waitpid(pidB, NULL, 0); // Ждём промежуточного родителя
        sleep(4); // Дать время дочернему процессу стать сиротой
        log_ps("Scenario B: Orphan adopted by systemd --user");
    }

    // --- Сценарий С: Зомби-процесс ---
    printf("\nScenario C: Zombie creation (no wait yet)\n");
    pid_t pidC = fork();
    if (pidC == 0)
    {
        printf("Child C: PID=%d, PPID=%d. Exiting immediately.\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    else
    {
        sleep(2); // Не вызываем wait сразу
        printf("Parent C: PID=%d. Child should be zombie now.\n", getpid());
        log_ps("Scenario C: Zombie process (before wait)");

        // Очищаем зомби
        waitpid(pidC, NULL, 0);
        printf("Parent C: Waited for child C, zombie cleared.\n");
        log_ps("Scenario C: Zombie cleared after wait()");
    }

    printf("\nMain process (PID=%d) finished.\n", getpid());
    return EXIT_SUCCESS;
}
