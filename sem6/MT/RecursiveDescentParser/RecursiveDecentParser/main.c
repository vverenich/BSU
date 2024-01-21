#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

//int E(), Edash(), T(), Tdash(), F();
int A(), Adash(), T(), B();


const char *cursor;
char string[64];

int main()
{
    puts("Enter the string");
    // scanf("%s", string);
    sscanf("b", "%s", string);
    cursor = string;
    puts("");
    puts("Input		 Action");
    puts("--------------------------------");

    if (A() && *cursor == '\0') {
        puts("--------------------------------");
        puts("String is successfully parsed");
        return 0;
    } else {
        puts("--------------------------------");
        puts("Error in parsing String");
        return 1;
    }
}

int A()
{
    if (*cursor == 'b') {
        printf("%-16s A -> bA'\n", cursor);
        cursor++;
        if (Adash()) {
            return SUCCESS;
        } else
            return FAILED;
    } else {
        return FAILED;
    }
}

int B()
{
    if (*cursor == 'a') {
        printf("%-16s B -> aAb \n", cursor);
        cursor++;
        if (A()) {
            if (*cursor == 'b') {
                cursor++;
                return SUCCESS;
            }
            else
                return FAILED;
        } else
            return FAILED;
    }

    return FAILED;
}

int Adash()
{
    printf("%-16s A' -> BA'|e\n", cursor);
    if (B()) {
        if (Adash()) {
            return SUCCESS;
        }
        else {
            return FAILED;
        }
    }
    else {
        printf("%-16s A' -> e\n", cursor);
        return SUCCESS;
    }
}





























int E()
{
    printf("%-16s E -> T E'\n", cursor);
    if (T()) {
        if (Edash())
            return SUCCESS;
        else
            return FAILED;
    } else
        return FAILED;
}

int Edash()
{
    if (*cursor == '+') {
        printf("%-16s E' -> + T E'\n", cursor);
        cursor++;
        if (T()) {
            if (Edash())
                return SUCCESS;
            else
                return FAILED;
        } else
            return FAILED;
    } else {
        printf("%-16s E' -> $\n", cursor);
        return SUCCESS;
    }
}

int T()
{
    printf("%-16s T -> F T'\n", cursor);
    if (F()) {
        if (Tdash())
            return SUCCESS;
        else
            return FAILED;
    } else
        return FAILED;
}

int Tdash()
{
    if (*cursor == '*') {
        printf("%-16s T' -> * F T'\n", cursor);
        cursor++;
        if (F()) {
            if (Tdash())
                return SUCCESS;
            else
                return FAILED;
        } else
            return FAILED;
    } else {
        printf("%-16s T' -> $\n", cursor);
        return SUCCESS;
    }
}

int F()
{
    if (*cursor == '(') {
        printf("%-16s F -> ( E )\n", cursor);
        cursor++;
        if (E()) {
            if (*cursor == ')') {
                cursor++;
                return SUCCESS;
            } else
                return FAILED;
        } else
            return FAILED;
    } else if (*cursor == 'i') {
        cursor++;
        printf("%-16s F -> i\n", cursor);
        return SUCCESS;
    } else
        return FAILED;
}
