#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc=1;
    char *sql;
    
    /* Open database */
    rc = sqlite3_open("lab.db", &db);

    if( rc ) {
       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       return(0);
    } else {
       fprintf(stderr, "Opened database successfully\n");
    }

    // Setting the view of selecting
    char *settings = ".mode column .headers on";
    sqlite3_exec(db, settings, callback, 0, &zErrMsg);

    while(1)
    {
        printf("Choose the option:" );
        printf("\n\t1) SELECT");
        printf("\n\t2) INSERT");
        printf("\n\t3) DELETE");
        printf("\n\t4) QUIT");

        printf("\n\nYour choice: ");
        int choice;
        scanf("%d", &choice);

        char firstPartOfQuery[300];
        char answer[300];
        char lastPartOfQuery[300];
        
        switch(choice)
        {
        case 1:
            printf("Choose the parameter:" );
            printf("\n\t1) by particular id");
            printf("\n\t2) by template with 1st determined char of name");
            printf("\n\t3) by particular city");

            printf("\n\nYour choice: ");
            scanf("%d", &choice);

            switch(choice)
            {
            case 1:
                printf("\n\nEnter the id:\n");
                scanf("%s", answer);

                // Initialize firstPartOfQuery and lastPartOfQuery arrays
                strcpy(firstPartOfQuery, "SELECT * from ENROLLEE where ID=");
                strcpy(lastPartOfQuery, ";");
                // sql = strcat(strcat(firstPartOfQuery, answer), lastPartOfQuery);
                break;
            case 2:
                printf("\n\nEnter the 1st char of name:\n");
                scanf("%s", answer);

                // Initialize firstPartOfQuery and lastPartOfQuery arrays
                strcpy(firstPartOfQuery, "SELECT * from ENROLLEE where NAME LIKE '");
                strcpy(lastPartOfQuery, "%';");
                //sql = strcat(strcat("SELECT * from ENROLLEE where NAME LIKE '", answer), "%';");
                break;
            case 3:
                printf("\n\nEnter the city name:\n");
                scanf("%s", answer);

                // Initialize firstPartOfQuery and lastPartOfQuery arrays
                strcpy(firstPartOfQuery, "SELECT * from ENROLLEE where CITY=");
                strcpy(lastPartOfQuery, ";");
                //sql = strcat(strcat("SELECT * from ENROLLEE where CITY=", answer), ";");
                break;
            default:
                printf("\n\nWrong input");
                return 0;
            }

            //

            break;
        case 2:
            printf("\n\nEnter values of columns SURNAME,NAME,PATRONYMIC,COUNTRY,CITY,SCORE without spaces and with quotes if needed:\n");
            scanf("%s", answer);

            // Initialize firstPartOfQuery and lastPartOfQuery arrays
            strcpy(firstPartOfQuery, "INSERT INTO ENROLLEE (SURNAME,NAME,PATRONYMIC,COUNTRY,CITY,SCORE) "  \
                                "VALUES(");
            strcpy(lastPartOfQuery, ");" \
                                "SELECT * from ENROLLEE;");
            /*
            sql = strcat(strcat("INSERT INTO ENROLLEE (SURNAME,NAME,PATRONYMIC,COUNTRY,CITY,SCORE) "  \
                                "VALUES(", answer), ");" \
                                "SELECT * from ENROLLEE;");
            */

            break;
        case 3:
            printf("\n\nEnter the id of the row to delete:\n");
            scanf("%s", answer);

            // Initialize firstPartOfQuery and lastPartOfQuery arrays
            strcpy(firstPartOfQuery, "DELETE from ENROLLEE where ID=");
            strcpy(lastPartOfQuery, ";" \
                                "SELECT * from ENROLLEE");
            /*
            sql = strcat(strcat("DELETE from ENROLLEE where ID=", answer), ";" \
                                "SELECT * from ENROLLEE");
            */

            break;
        case 4:
            return 0;
        default:
            printf("\n\nWrong input");
            return 0;
        }

        sql = strcat(strcat(firstPartOfQuery, answer), lastPartOfQuery);
        
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if( rc != SQLITE_OK ){
           fprintf(stderr, "SQL error: %s\n", zErrMsg);
           sqlite3_free(zErrMsg);
        } else {
           fprintf(stdout, "Records created successfully\n");
        }

    }
    sqlite3_close(db);
    return 0;
}