#!/usr/bin/awk -f

BEGIN {
    print "User_Name\t\tHome_Directory\tCommand_Interpreter"
    print "=================\t====================\t=================="
    FS=":"
    count=0;
}

{
    print $1 "\t" $6 "\t" $7
    if ($7 == "/bin/bash") {
        count++;
    }
}

END {
    print "=================\t====================\t=================="
    print "Total_records:" NR "\tRecords_with_bash:" count
}
