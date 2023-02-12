#!/bin/bash
function check_var
 {
  if [ -z $1 ]; then
  	echo "Ошибка ввода"
  	exit 1 
  fi
 }
function check_access {
  find_res=$(find $1 -perm -u+rwx)
  if [ -z $find_res ]; then
  	echo "WARNING. Доступ к файлу ограничен: " >&2
	stat -c "%A" $1
  fi
}
function move_file {
	read -p "Путь " path && check_var $path
	read -p "Имя файла " file_n && check_var $file_n
	check_access $file_n
	mv $file_n $path
	echo "Файл $file_n перемещен в $path"
}
function create_file {
	read -p "Имя файла" file_n && check_var $file_n
	touch $file_n
	echo "Файл $file_n создан"
}
function main {
	echo "Нажмите 1 чтобы переместить файл, 2 чтобы создать файл"
	read option
	case $option in
		1) move_file ;;
		2) create_file ;;
		 esac
	}
##	echo "Нажмите 1 чтобы переместить файл, 2 чтобы создать файл"
##	read option 
 ##       check_var $option	


main
