#include <stdio.h>
#include <book.h>

int main()
{
    FILE *fptr;
    fptr = fopen("//home//verchik//Projects/qt_projects//lab3_4_TP"
                 "//build-lab3_4_TP-Desktop-Debug//input", "r");

    unsigned numberOfBooks;
    fscanf(fptr, "%d", &numberOfBooks);

    fclose(fptr);

    Book *array = (Book*)calloc(numberOfBooks, sizeof(Book));
    unsigned arraySize = readBooksFromFile(array);
    writeBooksToFile(array, arraySize);

    free(array);
    return 0;
}
