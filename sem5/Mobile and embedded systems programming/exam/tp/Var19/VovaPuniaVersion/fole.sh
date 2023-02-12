#!/bin/bash

 read -p "Имя файла " file_n

 if test -f "$file_n"; then
    echo "$file_n exists."
	LAST="$(wc -c $file_n | awk '{print $1}')"
	if (( $(echo "$LAST < 1000" | bc -l) )) ; then
	{
		echo "B"
		echo $LAST
	}
	else
	{	
		if (( $(echo "$LAST < 1000000" | bc -l) )) ; then
        	{
			echo "KB"
                	D=$(bc<<<"scale=3;$LAST/1000")
	                echo "$D"
        	}
		else
		{
			echo "MB"
			D=$(bc<<<"scale=3;$LAST/1000000")
	        	echo "$D"
		}
		fi
        }
	fi

    ls -la | grep $file_n | awk '{print $3}'
 fi


 if [ -d "$file_n" ]; then
    echo "$file_n is a directory."
 fi
