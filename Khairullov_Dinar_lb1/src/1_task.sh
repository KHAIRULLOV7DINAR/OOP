#!/bin/bash

# Получение имени файла для записи результатов
if [ -z "$1" ]; then
	echo "Пожалуйста, укажите имя выходного файла."
	exit 1
fi

output_file="$1"

#Нахождение файла каждого типа, запись в выходной файл полный путь а
# Находим и записываем в выходной файл один пример каждого типа файла с полным путем
echo "Обычный файл:" > "$output_file"
ls -lR | grep -E '^-.*' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"

echo "Блочное устройство(b):" >> "$output_file"
ls -lR | grep -E '^b' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"

echo "Символьное устройство(c):" >> "$output_file"
ls -lR | grep -E '^c' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"

echo "Директория(d):" >> "$output_file"
ls -lR | grep -E '^d' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"

echo "Символьная ссылка(l):" >> "$output_file"
ls -lR | grep -E '^l' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"

echo "FIFO(p):" >> "$output_file"
ls -lR | grep -E '^p' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"

echo "Сокет(s):" >> "$output_file"
ls -lR | grep -E '^s' | head -n 1 | awk '{print "'$(pwd)'/"$NF}' >> "$output_file"
echo "==================================" >> "$output_file"
