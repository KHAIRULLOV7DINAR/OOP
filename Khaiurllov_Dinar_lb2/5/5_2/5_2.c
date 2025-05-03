#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>


void print_priority(const char *process_name, pid_t pid)
{
    int prio = getpriority(PRIO_PROCESS, pid); // Получаем приоритет для указанного PID
    if (prio == -1 && errno != 0)
    {
        perror("Getpriority error\n");
    }
    else
    {
        printf("%-40s (PID: %d): Current priority (nice): %d\n", process_name, pid, prio);
    }
}


int main()
{
    //System process
    pid_t system_process_pid = 15; 
    printf("Comparing and changing priorities of system and user processes\n\n");
    printf("------System process------\n");
    print_priority("System process", system_process_pid);

    pid_t old_priority = getpriority(PRIO_PROCESS, system_process_pid);
    // Пытаемся изменить приоритет системного процесса
    printf("\nTrying to change system process priority (PID: %d) increasing by  10...\n", system_process_pid);
    
    if (setpriority(PRIO_PROCESS, system_process_pid, old_priority+10) == -1)
    {
      perror("Error setpriority for system process\n");
    }
    else
    {
      printf("System process priority was changed.\n");
    }

    // Проверяем приоритет системного процесса после попытки изменения
    print_priority("System process priority after changes\n", system_process_pid);
    // Возвращаем старый приоритет
    setpriority(PRIO_PROCESS, system_process_pid, old_priority);              

    printf("\n------User process------\n");
    print_priority("User process before changes", getpid());

    // Пытаемся увеличить приоритет (уменьшить значение nice)
    printf("\nTrying to set priority to -10...\n");
    
    if (setpriority(PRIO_PROCESS, getpid(), -10) == -1)
    {
        perror("Error setpriority");
    }

    print_priority("User process priority after changes", getpid());

    printf("\n=== End ===\n");
    return 0;
}
