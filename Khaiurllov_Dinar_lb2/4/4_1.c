#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <string.h>

int global_var = 1;
int shared_fd;  // Общий файловый дескриптор
int* heap_var;  // Указатель на переменную в куче
pthread_mutex_t heap_mutex = PTHREAD_MUTEX_INITIALIZER;

void *pthread_function(void *arg)
{
    int thread_num = *(int *)arg;
    
    pthread_mutex_lock(&heap_mutex);
    
    printf("Pthread %d: PID = %d, PPID = %d, TID = %ld\n", thread_num, getpid(), getppid(), syscall(SYS_gettid));
    char buffer[50];
    
    int local_var = 10;
    
    // Демонстрация работы с кучей
    //pthread_mutex_lock(&heap_mutex);
    printf("Pthread %d: heap_var = %d (address: %p)\n", 
           thread_num, *heap_var, heap_var);
    *heap_var += 1;
    //pthread_mutex_unlock(&heap_mutex);
    
    // Запись в файл
    snprintf(buffer, sizeof(buffer), "Pthread %d writing to file\n", thread_num);
    write(shared_fd, buffer, strlen(buffer));
    
    printf("Pthread %d: wrote to fd %d\n", thread_num, shared_fd);
    printf("Pthread %d: PATH=%s\n", thread_num, getenv("PATH"));
    printf("Pthread %d: local_var = %d\n", thread_num, local_var);
    local_var++;
    
    global_var *= 2;
    printf("Pthread %d: global_var = %d\n", thread_num, global_var);
    printf("-----------------------------------\n");
    
    printf("Pthread %d: завершил работу.\n", thread_num);
    
    pthread_mutex_unlock(&heap_mutex);
    
    return NULL;
}

int clone_function(void *arg)
{
    int thread_num = *(int *)arg;
    pthread_mutex_lock(&heap_mutex);
    printf("Clone-thread %d: PID = %d, PPID = %d, TID = %ld\n", thread_num, getpid(), getppid(), syscall(SYS_gettid));
    char buffer[50];

    int local_var = 10;
    
    // Демонстрация работы с кучей
    //pthread_mutex_lock(&heap_mutex);
    printf("Clone-thread %d: heap_var = %d (address: %p)\n", 
           thread_num, *heap_var, heap_var);
    *heap_var += 1;
    //pthread_mutex_unlock(&heap_mutex);
    
    // Запись в файл
    snprintf(buffer, sizeof(buffer), "Clone-thread %d writing to file\n", thread_num);
    write(shared_fd, buffer, strlen(buffer));
    
    printf("Clone-thread %d: wrote to fd %d\n", thread_num, shared_fd);
    printf("Clone-thread %d: PATH=%s\n", thread_num, getenv("PATH"));
    printf("Clone-thread %d: local_var = %d\n", thread_num, local_var);
    local_var++;
    
    global_var *= 2;
    printf("Clone-thread %d: global_var = %d\n", thread_num, global_var);
    printf("-----------------------------------\n");
    
    printf("Clone-thread %d: завершил работу.\n", thread_num);
    
    pthread_mutex_unlock(&heap_mutex);
    
    return 0;
}

int main() {
    // Выделяем память в куче
    heap_var = (int*)malloc(sizeof(int));
    *heap_var = 100;
    printf("Main: initial heap_var = %d (address: %p)\n", *heap_var, heap_var);
    printf("-----------------------------------\n");
   

    // Создаем файл для демонстрации
    shared_fd = open("shared_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (shared_fd == -1)
    {
        perror("open");
        free(heap_var);
        exit(1);
    }
    
    pthread_t thread1, thread2;
    int num1 = 1, num2 = 2;

    // Создаем pthread-нити
    pthread_create(&thread1, NULL, pthread_function, &num1);
    pthread_create(&thread2, NULL, pthread_function, &num2);

    // Создаем поток через clone()
    int num3 = 3;
    char stack[4096];
    pid_t clone_pid = clone(
        clone_function,
        stack + 4096,
        CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD,
        &num3
    );

    if (clone_pid == -1)
    {
        perror("clone");
        close(shared_fd);
        free(heap_var);
        exit(1);
    }

    // Ждем завершения всех нитей
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sleep(1);
    waitpid(clone_pid, NULL, 0);

    // Выводим итоговое значение переменной в куче
    printf("\nFinal heap_var value = %d\n", *heap_var);

    // Освобождаем ресурсы
    close(shared_fd);
    free(heap_var);
        
    return 0;
}
