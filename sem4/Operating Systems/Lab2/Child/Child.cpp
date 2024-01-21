#include <iostream>
#include <cstdlib>
#include <vector>

void printArray(const std::vector<int>& array) {
    for (const auto& number : array) {
        std::cout << number << " ";
    }
}

int main(int argc, char* argv[])
{

    if (argc < 2) {
        return 1;
    }

    //getting the array size
    int arraySize = std::atoi(argv[1]);
    std::vector<int> myArray;

    //filling array
    myArray.resize(arraySize);
    for (int i{ 0 }; i < arraySize; ++i) {
        myArray.at(i) = std::atoi(argv[i + 2]);
    }

    std::cout << "Initial array:\n";
    printArray(myArray);
    std::cout << "\n\n";

    //initializing of A and B
    int A = std::atoi(argv[arraySize + 2]);
    int B = std::atoi(argv[arraySize + 3]);

    std::cout << "Range: [" << A << ", " << B << "]";
    std::cout << "\n\n";

    //position of the element from the left side, that we are gonna swap with the element of [A,B] range
    int positionToSwap{ 0 };

    //swapping the appropriate elements
    for (int i{ 0 }; i < arraySize; ++i) {
        if (myArray.at(i) <= B && myArray.at(i) >= A) {
            std::swap(myArray.at(positionToSwap), myArray.at(i));
            ++positionToSwap;
        }
    }

    //zeroing of non-corresponding elements
    for (int i{ positionToSwap }; i < arraySize; ++i) {
        myArray.at(i) = 0;
    }

    std::cout << "Final array:\n";
    printArray(myArray);

    std::cout << "\nPress any key to exit: ";
    char key;
    std::cin >> key;
    return 0;
}