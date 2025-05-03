#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define FILENAME "shared_data.txt"
#define FILE_MODE 0644

void write_to_file(int fd, const char* message)
{
    if (write(fd, message, strlen(message)) == -1)
    {
        perror("Error write in file.\n");
        exit(EXIT_FAILURE);
    }
}

void setup_file(int* fd)
{
    *fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
    if (*fd == -1) {
        perror("Error file open.\n");
        exit(EXIT_FAILURE);
    }
}

void process_operations(int fd, const char* process_type)
{
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s process (PID: %d)\n", process_type, getpid());
    write_to_file(fd, buffer);
}

int main()
{
    int file_descriptor;
    setup_file(&file_descriptor);

    pid_t process_id = fork();
    if (process_id == -1)
    {
        perror("Error creating process");
        close(file_descriptor);
        return EXIT_FAILURE;
    }

    if (process_id == 0)
    {
        process_operations(file_descriptor, "Child process");
    }
    else
    {
        process_operations(file_descriptor, "Parent process");
        wait(NULL); // Ожидание завершения дочернего процесса
    }

    close(file_descriptor);
    return EXIT_SUCCESS;
}
