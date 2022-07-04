#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdlib.h>
#include <string.h>

typedef struct DATE Date;
struct DATE
{
    uint m_day;
    uint m_month;
    uint m_year;
};

typedef struct PRODUCT Product;
struct PRODUCT
{

    char m_name[30];
    int  m_price;
    Date m_dateOfManufacture;
    Date m_expirationDate;
    int  m_number;
    char m_manufacturer[30];
};

void createArrayOfProducts(Product *arrayPtr, int size);

int compareProductsByDate(const Product *first, const Product *second);

void printProductInfo(Product *product);

void printProductsSortedByDateOfManufacture(Product *array, int size);

void printProductsThatExpireInTwoDays(Product *array, int size, Date *today);

int compareProductsByManufacturer(const Product *p1,const Product *p2);

void printNumberOfProductsForEachManufacturer(Product *array, int size);

void printTopPricedProduct(Product *array, int size, Date *today);

#endif





















