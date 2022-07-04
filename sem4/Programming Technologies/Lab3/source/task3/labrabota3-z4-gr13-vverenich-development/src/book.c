#include "book.h"

unsigned readBooksFromFile(Book *array)
{
    FILE *fptr;
    fptr = fopen("//home//verchik//Projects/qt_projects//lab3_4_TP"
                 "//build-lab3_4_TP-Desktop-Debug//input", "r");

    if(fptr == NULL)
    {
       printf("Error opening input file");
       exit(1);
    }

    unsigned numberOfBooks;
    fscanf(fptr, "%d", &numberOfBooks);

    for(unsigned i = 0; i < numberOfBooks; ++i)
    {
        fscanf(fptr, "%s", &array[i].m_name);
        fscanf(fptr, "%s", &array[i].m_authorSurname);
        fscanf(fptr, "%s", &array[i].m_authorName);
        fscanf(fptr, "%d", &array[i].m_year);
        fscanf(fptr, "%s", &array[i].m_publisher);
        fscanf(fptr, "%d", &array[i].m_cost);
        fscanf(fptr, "%d", &array[i].m_price);
        fscanf(fptr, "%d", &array[i].m_profit);
    }
    fclose(fptr);

    return numberOfBooks;
}

void writeBooksToFile(Book *array, unsigned size)
{
    FILE *fptr;
    fptr = fopen("//home//verchik//Projects/qt_projects"
                 "//lab3_4_TP//build-lab3_4_TP-Desktop-Debug//output", "w");

    if(fptr == NULL)
    {
       printf("Error opening output file");
       exit(1);
    }

    for(unsigned i = 0; i < size; ++i)
    {
        if(array[i].m_authorSurname[0] == 'K'){
            fprintf(fptr, "\nBook's number in array: %d", i+1);
            fprintf(fptr, "\n\tname: %s", array[i].m_name);
            fprintf(fptr, "\n\tauthor surname: %s", array[i].m_authorSurname);
            fprintf(fptr, "\n\tauthor name: %s", array[i].m_authorName);
            fprintf(fptr, "\n\tyear: %d", array[i].m_year);
            fprintf(fptr, "\n\tpublisher: %s", array[i].m_publisher);
            fprintf(fptr, "\n\tcost: %d", array[i].m_cost);
            fprintf(fptr, "\n\tprice: %d", array[i].m_price);
            fprintf(fptr, "\n\tprofit: %d", array[i].m_profit);
        }
    }
    fclose(fptr);
}
