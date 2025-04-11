#!/bin/bash

#Получение имени файла, на которые ссылаются символьные ссылки:
if [ -z "$1" ]; then
    echo "Использование: $0 <filename>"
    exit 1
fi

target=$(realpath "$1")

#Поиск символьных ссылок на полученный файл с помощью find:
find ~/ -type l 2>/dev/null | while read LINK; do
    # Проверка, на какой файл указывает ссылка
    if [ "$(readlink -f "$LINK")" == "$target" ]; then
        echo "$LINK"
    fi
done




