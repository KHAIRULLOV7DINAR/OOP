#!/bin/bash

#Считывание имени файла
if [ -z "$1" ]; then
    echo "Ошибка: формат ввода 'Путь к файлу'"
    exit 1
fi

linked_file="$1"

#Получение inode файла для нахождения жестких ссылок
inode=$(ls -i "$linked_file" | awk '{print $1}')

if [ -z "$inode" ]; then
  echo "Ошибка получения inode для заданного файла"
  exit 1
fi

#Вывод информации о файлах с найденным inode
ls -liR ~/ 2>/dev/null | grep $inode
