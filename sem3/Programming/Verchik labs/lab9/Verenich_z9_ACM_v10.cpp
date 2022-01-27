#include <iostream>

int getNumberOfSignificantDigits(int n) {
    _asm {
        mov eax, 0;
        mov ebx, n;
    begin:
        test ebx, 1;
        jz yoohoo;
        add eax, 1;
    yoohoo:
        shr ebx, 1;
        cmp ebx, 0;
        je end;
        jmp begin;
    end:;
    }
}

int main()
{
    std::cout << "Enter number: \n";
    int n;
    std::cin >> n;

    while(n<0) {
        std::cout << "Enter natural number!\n";
        std::cout << "Your number: ";
        std::cin >> n;
        std::cout<< "\n";
    }
    
    std::cout << "Number of significant digits in binary notation: " << getNumberOfSignificantDigits(n);
}

