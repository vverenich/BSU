#include <iostream>
#include<string.h>
int lastSymbol;
char* ltrim(const char* string) {
    int lastSymbol= 0;
    while (string[lastSymbol] != '\0') {
        ++lastSymbol;
    }

    --lastSymbol;
    while (( string[lastSymbol] == ' ') && (lastSymbol >= 0)) {
        --lastSymbol;
    }
    
    char* newStr = new char[lastSymbol + 2];
    for (int i = 0; i < lastSymbol + 1; ++i) {
        newStr[i] = string[i];
    }

    newStr[lastSymbol+1] = '\0';
    for (int i = 0; i <= lastSymbol; ++i) {
        std::cout << newStr[i];
    }
    std::cout << "\n" << lastSymbol+1;
    return newStr;
}

int getValue() {
    while (true) {
        std::cout << "Enter max number of symbols in your string(any  natural number):";
        int N;
        std::cin >> N;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// насколько я понял входной буфер может вместить максимум 32768=2^15 символов
            std::cout << "\nYou made an illegal choice. ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return N;
        }
    }
}
int main(){
    int N = getValue();
    ++N;
    char* s = new char[N];
    std::cout << "\nEnter your string: ";
    std::cin.getline(s, N);
    char* stroka = new char[N];
    stroka=ltrim(s);

    std::cout << "\nYour new string is ";
    for (int i = 0; i < lastSymbol + 1; ++i) {
        std::cout << stroka[i];
    }
    std::cout << ", its length is " << lastSymbol + 1;
    delete[] stroka;   
    delete [] ltrim(s);
    delete[] s;
   return 0;
}

