#include <stdio.h>
#include <product.h>

int main()
{
    int numberOfProducts;
    printf("Enter N: ");
    scanf("%d", &numberOfProducts);

    Date *today = (Date*)calloc(numberOfProducts, sizeof (Date));
    printf("Enter today's date: ");
    scanf("%d %d %d", &today->m_day, &today->m_month, &today->m_year);

    Product *array = (Product*)calloc(numberOfProducts, sizeof (Product));
    createArrayOfProducts(array, numberOfProducts);
    printProductsSortedByDateOfManufacture(array,numberOfProducts);
    printProductsThatExpireInTwoDays(array, numberOfProducts, today);
    printNumberOfProductsForEachManufacturer(array, numberOfProducts);
    printTopPricedProduct(array, numberOfProducts, today);
    return 0;
}
