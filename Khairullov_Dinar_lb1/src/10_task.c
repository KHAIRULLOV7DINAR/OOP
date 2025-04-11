#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
// открытие файла по переданному как аргумент имени
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
// вывод символов файла до символа конца файла
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (putchar(ch) == EOF)
        {
            perror("Ошибка вывода");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    if (ferror(file))
    {
        perror("Ошибка чтения файла");
        fclose(file);
        exit(EXIT_FAILURE);
    }
// закрытие файла 
    fclose(file);
    return 0;
}
