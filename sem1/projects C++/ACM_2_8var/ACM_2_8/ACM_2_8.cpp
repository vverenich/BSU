#include <iostream>
#include <string>
#include <iomanip>

char* GetNum(char* string, size_t strSize)
{
	char *tempstr = new char[255]{32};
	_asm
	{
		mov edi, string
		mov ecx, strSize
		mov eax, '('
		repnz scasb
		test ecx, ecx
		jz FINISH
		mov ebx, strSize
		sub ebx, ecx
		mov ecx, ebx
		mov edx, ecx
		mov esi, string
		mov edi, tempstr
		dec ecx
		rep movsb
		mov ecx, strSize
		sub ecx, edx
		mov eax, ')'
		xchg esi, edi
		repnz scasb
		test ecx, ecx
		jz FINISH
		xchg esi, edi
		inc ecx
		rep movsb
		FINISH :
		mov string, edi
	}
	return tempstr;
}

int main()
{
	std::string str;
	std::getline(std::cin, str);
	char* newstr = GetNum((char*)str.data(), str.length());
	std::cout  << newstr << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}