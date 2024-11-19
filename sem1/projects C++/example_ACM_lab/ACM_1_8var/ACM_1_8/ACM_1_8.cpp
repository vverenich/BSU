
#include "pch.h"
#include <iostream>


int GetNum(int num)
{
	_asm
	{
		mov eax, num
		mov ecx, 2
		mov ebx, 0
		cmp eax, 0
		jge Loop1
		imul eax, -1
		inc ebx
		Loop1:
		cdq
			div ecx
			cmp edx, 1
			jz ONE
			BACK :
		test eax, eax
			jz EXIT
			jmp Loop1
			ONE :
		inc ebx
			jmp BACK
			EXIT :
		mov eax, ebx

	}


}

int main()
{
	int num = 0;
	std::cin >> num;
	int amount = GetNum(num);
	std::cout << amount;
	system("pause");
	return EXIT_SUCCESS;
}