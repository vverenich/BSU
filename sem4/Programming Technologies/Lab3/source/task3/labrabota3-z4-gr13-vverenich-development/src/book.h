#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BOOK Book;
struct BOOK
{
    char m_name[30];
    char m_authorSurname[30];
    char m_authorName[30];
    unsigned m_year;
    char m_publisher[30];
    unsigned m_cost;
    unsigned m_price;
    unsigned m_profit;
};

unsigned readBooksFromFile(Book *array);

void writeBooksToFile(Book *array, unsigned size);

#endif
