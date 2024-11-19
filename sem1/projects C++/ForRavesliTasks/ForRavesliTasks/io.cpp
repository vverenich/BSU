#include<iostream>
int readNumber() {
    std::cout << "Enter number: ";
    int a;
    std::cin >> a;
    return a;
}

void writeAnswer(int res) {
    std::cout << "Result: " << res;
}