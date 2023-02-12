#! /usr/bin/bash

appendfile(){
echo $1>> file.txt
ls -l $2 >> file.txt;
}

echo 'Hi there!'
echo 'Input the year of birth for converting (yyyy)'
read year;

num=$(printf '%o\n' $year);
mod=$(echo $num |awk '{print substr($0,0,3)}');
mainMask=$(umask);

touch file.txt;

umask $mod;
touch example.txt;
#echo 'Temniakov Yan Vitalevich\n3-13b' >> example.txt;
echo 'Current mask' $(umask);

echo 'Input path to file:';
read path;

appendfile 1 $path;
umask $mainMask;
echo 'Current mask' $(umask);
appendfile 2 $path;