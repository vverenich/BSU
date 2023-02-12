#!/usr/bin/awk -f
function file_exists(file){
	if ((getline _ < file) >= 0) { return 1; }
	else { print("Ошибка чтения файла!"); exit 1 }
}
BEGIN {	
	print("Input file: ", ARGV[1])
	file_exists(ARGV[1]) 
	print("Ouput file: ", ARGV[2]) 
	RS=""
	FS="\n"
}
{
	print($1,":",$3) > ARGV[2];
}

##sed '$d' ARGV[2] > buf
