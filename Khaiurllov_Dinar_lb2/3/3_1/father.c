#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


int main()
{
    pid_t son1_pid, son2_pid, son3_pid;

    // son1 (реакция по умолчанию)
    if ((son1_pid = fork()) == 0)
    {
        execl("./son1", "son1", NULL);
        //случай ошибки execl
        perror("execl son1");
        exit(1);
    }

    // son2 (игнорирование сигнала)
    if ((son2_pid = fork()) == 0)
    {
        execl("./son2", "son2", NULL);
        //случай ошибки execl
        perror("execl son2");
        exit(1);
    }

    // son3 (перехват сигнала)
    if ((son3_pid = fork()) == 0)
    {
        execl("./son3", "son3", NULL);
        //случай ошибки execl
        perror("execl son3");
        exit(1);
    }
    
    // даем потомкам время запуститься
    sleep(3);

    printf("Father process sending SIGTERM signal to all son processes.\n");
    
    //запись до отправки сигналов
    system("ps -s >> signals_before_log.txt");
  
    // отправка SIGTERM каждому из потомков
    kill(son1_pid, SIGTERM); // по умолчанию
    kill(son2_pid, SIGTERM); // игнорирование
    kill(son3_pid, SIGTERM); // перехват

    sleep(3);
    //запись
    system("ps -s >> signals_after_log.txt");

    // Ожидаем завершения потомков
    wait(NULL);
    wait(NULL);
    
    //запись после wait
    system("ps -s >> signals_after_wait_log.txt");
    
    wait(NULL);
  

    printf("Father: all children terminated. End of the process.\n");
    return 0;
}
