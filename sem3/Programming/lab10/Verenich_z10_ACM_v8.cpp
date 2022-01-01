#include<iostream>
#include<string>

int getLengthOfLargestWord—PP(const char* str, int n) {
	int result{ 0 };
	int current{ 0 };
	for (size_t i{ 0 }; i < n; ++i) {
		if (str[i] != ' ') {
			++current;
			continue;
		}
		if (result < current) {
			result = current;
		}
		current = 0;
	}
	if (result < current) {
		result = current;
	}
	return result;
}

int getLengthOfLargestWordASM(const char* str, int n) {
	_asm {
		mov eax, 0;
		mov ebx, n;
		mov ecx, 0;
		mov edx, str;
	begin:
		sub ebx, 1;
		cmp[edx][ebx], 32;
		je is_space;
		add ecx, 1;
		cmp ebx, 0;
		je end;
		jmp begin;
	is_space:
		cmp ecx, eax;
		jg swap;
		jmp next;
	next:
		mov ecx, 0;
		cmp ebx, 0;
		je end;
		jmp begin;
	swap:
		mov eax, ecx;
		jmp next;
	final_swap:
		mov eax, ecx;
		jmp end;
	end:
		cmp ecx, eax;
		jg final_swap;
	}
}


int main() {
	std::cout << "Enter your string: ";
	std::string words;
	std::getline(std::cin, words, '\n');
	const char* arr = words.c_str();
	std::cout << "ASM: " << getLengthOfLargestWordASM(arr, words.size()) << "\n";
	std::cout << "CPP: " << getLengthOfLargestWord—PP(arr, words.size());
}