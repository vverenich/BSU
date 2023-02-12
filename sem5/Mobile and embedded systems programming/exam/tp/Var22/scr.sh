#!/bin/bash

MENU=(
    "удалить файл"
    "создать файл"
    "изменить владельца файла"
    "вывести файлы"
    "выйти"
)

select menu in "${MENU[@]}" ; do
    case $REPLY in
        1)
          read -p "Введите имя файла: " filename
          echo "Вы ввели $filename"
          rm -rf "$filename"
          echo "Файл удален $filename"
        ;;
        2)
          read -p "Введите имя файла: " filename
          echo "Вы ввели $filename"
          touch "$filename"
          echo "Файл создан $filename"
        ;;
        3)
          read -p "Введите имя файла: " filename
          echo "Вы ввели $filename"
          read -p "Введите имя пользователя: " user
          sudo chown "$user" "$filename"
        ;;
        4)
          ls -l
        ;;
        5) break ;;
        *) echo "Invalid option $REPLY"
        ;;
    esac
done



# echo "Select the operation: "

# select opt in add subtract multiply divide quit; do

#   case $opt in
#     add)
#       read -p "Enter the first number: " n1
#       read -p "Enter the second number: " n2
#       echo "$n1 + $n2 = $(($n1+$n2))"
#       ;;
#     subtract)
#       read -p "Enter the first number: " n1
#       read -p "Enter the second number: " n2
#       echo "$n1 - $n2 = $(($n1-$n2))"
#       ;;
#     multiply)
#       read -p "Enter the first number: " n1
#       read -p "Enter the second number: " n2
#       echo "$n1 * $n2 = $(($n1*$n2))"
#       ;;
#     divide)
#       read -p "Enter the first number: " n1
#       read -p "Enter the second number: " n2
#       echo "$n1 / $n2 = $(($n1/$n2))"
#       ;;
#     quit)
#       break
#       ;;
#     *) 
#       echo "Invalid option $REPLY"
#       ;;
#   esac
# done