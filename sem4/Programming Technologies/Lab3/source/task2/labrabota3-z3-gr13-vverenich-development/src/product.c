#include <product.h>


void createArrayOfProducts(Product *arrayPtr, int size)
{
    Product *product = (Product*)calloc(1,sizeof (Product));

    for(int i = 0; i < size; ++i)
    {
        printf("Enter the name of product: ");
        scanf("%s", &product->m_name);

        printf("Enter price of the product: ");
        scanf("%d", &product->m_price);

        printf("Enter the date of manufacture: ");
        scanf("%d %d %d", &product->m_dateOfManufacture.m_day,
              &product->m_dateOfManufacture.m_month,
              &product->m_dateOfManufacture.m_year);

        printf("Enter expiration date: ");
        scanf("%d %d %d", &product->m_expirationDate.m_day,
              &product->m_expirationDate.m_month,
              &product->m_expirationDate.m_year);

        printf("Enter the number of products: ");
        scanf("%d", &product->m_number);

        printf("Enter the name of manufacturer: ");
        scanf("%s", &product->m_manufacturer);

        arrayPtr[i] = *product;
    }
}

int compareProductsByDate(const Product *first, const Product *second)
{
    /**
     * Compare by year at first.
     */
    if (first->m_dateOfManufacture.m_year < second->m_dateOfManufacture.m_year)
    {
        return -1;
    }

    if(first->m_dateOfManufacture.m_year > second->m_dateOfManufacture.m_year){
        return +1;
    }

    /**
     * Compare by month then.
     */
    if (first->m_dateOfManufacture.m_month < second->m_dateOfManufacture.m_month)
    {
        return -1;
    }

    if(first->m_dateOfManufacture.m_month > second->m_dateOfManufacture.m_month){
        return +1;
    }

    /**
     * Finally, compare by day.
     */
    if (first->m_dateOfManufacture.m_day < second->m_dateOfManufacture.m_day)
    {
        return -1;
    }

    if(first->m_dateOfManufacture.m_day > second->m_dateOfManufacture.m_day){
        return +1;
    }

    /**
     * In case if no one statement above doesn't return smth,
     * then we've got two equal dates.
     */
    return 0;
}

void printProductInfo(Product *product)
{
    printf("\n\tname: %s", product->m_name);
    printf("\n\tprice: %d", product->m_price);
    printf("\n\tmanufacture date: %d %d %d", product->m_dateOfManufacture.m_day,
           product->m_dateOfManufacture.m_month,
           product->m_dateOfManufacture.m_year);
    printf("\n\texpiration date: %d %d %d", product->m_expirationDate.m_day,
           product->m_expirationDate.m_month,
           product->m_expirationDate.m_year);
    printf("\n\tnumber of products: %d", product->m_number);
    printf("\n\tmanufacturer: %s", product->m_manufacturer);
    printf("\n\n");
}

void printProductsSortedByDateOfManufacture(Product *array, int size)
{
    qsort(array, size, sizeof (Product), compareProductsByDate);

    printf("\n-------Products sorted by date of manufacture-------");
    for(int i = 0; i < size; ++i)
    {
        printf("\nproduct %d", i+1);
        printProductInfo(&array[i]);
    }
}

void printProductsThatExpireInTwoDays(Product *array, int size, Date *today)
{
    printf("\n-------Products that expire in two days-------");
    for(int i = 0 ; i < size ; ++i)
    {
        if(array[i].m_expirationDate.m_year == today->m_year &&
           array[i].m_expirationDate.m_month == today->m_month &&
           array[i].m_expirationDate.m_day - today->m_day == 2)
        {
            printProductInfo(&array[i]);
        }
    }
}

int compareProductsByManufacturer(const Product *p1,const Product *p2)
{
    return strcmp(p1->m_manufacturer, p2->m_manufacturer);
}

void printNumberOfProductsForEachManufacturer(Product *array, int size)
{
    qsort(array, size, sizeof (Product), compareProductsByManufacturer);

    char lastManufacturer[30];
    strcpy(lastManufacturer, array[0].m_manufacturer);
    int lastManufacturerProductsNumber = 0;

    printf("\n-------Number of products for each manufacturer-------");
    for (int i = 0; i < size ; ++i)
    {
        if(strcmp(lastManufacturer,array[i].m_manufacturer) == 0){
            lastManufacturerProductsNumber += array[i].m_number;
        }else{
            printf("%s: %d\n", lastManufacturer, lastManufacturerProductsNumber);
            strcpy(lastManufacturer, array[i].m_manufacturer);
            lastManufacturerProductsNumber = 0;
        }
    }
}

void printTopPricedProduct(Product *array, int size, Date *today)
{
    char productName[30];
    strcpy(productName, array[0].m_name);
    int productPrice = 0;

    for(int i = 0; i < size; ++i)
    {
        if(array[i].m_expirationDate.m_year >= today->m_year &&
           array[i].m_expirationDate.m_month >= today->m_month &&
           array[i].m_expirationDate.m_day >= today->m_day)
        {
            if(array[i].m_price > productPrice){
                productPrice = array[i].m_price;
                strcpy(productName, array[i].m_name);
            }
        }
    }

    printf("\n-------top priced product-------");
    printf("\nname: %s", productName);
    printf("\nprice: %d", productPrice);
    printf("\n\n");
}
