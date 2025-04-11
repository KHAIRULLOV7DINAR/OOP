#!/bin/bash

#Создание тестового каталога:
mkdir 7_task_dir
echo "Создан каталог 7_task_dir"

#Вывод размера каталога:
du -sh 7_task_dir 

#Добавление файлов и каталогов:
for i in {1..5}; do
    echo "Файл номер $i" > 7_task_dir/file$i.txt
    echo "Добавлен файл номер $i"
    mkdir 7_task_dir/7_task_dir_sub$i
    echo "Добавлен каталог номер $i"
    du -sh 7_task_dir 
done

#Вывод размера каталога после изменений:
du -sh 7_task_dir

#Рекурсивное удаление файлов и каталогов: 
rm -rf 7_task_dir/*
echo "Удалены все файлы и каталоги в директории 7_task_dir"

#Вывод размера каталога после изменений:
du -sh 7_task_dir 

#Удаление каталога:
rmdir 7_task_dir
echo "Каталог был удален."
