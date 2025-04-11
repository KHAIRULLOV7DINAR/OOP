#!/bin/bash

#Считывание имени файла:
if [ -z "$1" ]; then
    echo "Ошибка: формат ввода 'Путь к файлу'"
    exit 1
fi

#Нахождение полного пути до файла:
path_linked_file=$(realpath "$1")

COUNTER=0

#Поиск символьных ссылок и подсчет их количества:
while read -r symlink; do
    if [ "$(realpath  "$symlink" 2>/dev/null)" = "$path_linked_file" ]; then
        echo "$symlink"
        COUNTER=$((COUNTER + 1))
    fi
done < <(find ~/ -type l 2>/dev/null)

#Вывод количества найденных символьных ссылок:
echo "Кол-во найденных символьных ссылок: $COUNTER"
