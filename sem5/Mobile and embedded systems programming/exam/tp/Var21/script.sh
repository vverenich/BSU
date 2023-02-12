#!/bin/bash

cat /etc/passwd | 
awk -F: 'BEGIN {printf("%24s %24s %24s \n%72s\n",
		       "username", "home dir", "shell",
	"--------------------------------------------------------------------------");
		countAll = 0; 
		countSpecific = 0} 
	       {printf("%24s %24s %24s \n" , $1, $6, $7);
		if (100 <= $4 && $4 <= 200)
			countSpecific++
		countAll++}
	 END   {printf("%72s \n%36s %24d \n%36s %24d",
	"--------------------------------------------------------------------------",
 		       "count of rows(100<=groupid<=200):", countSpecific,
		       "count all:", countAll )}' |
tee > no-login-users.txt
