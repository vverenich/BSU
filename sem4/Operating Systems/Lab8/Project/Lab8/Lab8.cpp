#include <windows.h>
#include <iostream>
#include <string>

#define PHILOSOFER_COUNTS 5
#define EATING_TIME 100
#define THINKING_TIME 200

bool forks[PHILOSOFER_COUNTS];
CRITICAL_SECTION cs[PHILOSOFER_COUNTS];
int philosoferNumbers[] = { 1, 2, 3, 4, 5 };
CRITICAL_SECTION outputSection;

void eat(int philId);
void think(int philId);
DWORD WINAPI doPhilosofie(LPVOID params);
int left(int i);
int right(int i);

int main() {
    HANDLE threads[PHILOSOFER_COUNTS];

    //Инициализируем критическую секцию
    for (int i = 0; i < PHILOSOFER_COUNTS; ++i) {
        InitializeCriticalSection(&cs[i]);
    }
	InitializeCriticalSection(&outputSection);

    //Запустим 5 потоков
    for (int i = 0; i < 5; ++i) {
        threads[i] = CreateThread(nullptr, 0, doPhilosofie, &philosoferNumbers[i], 0, nullptr);
    }

    WaitForMultipleObjects(PHILOSOFER_COUNTS, threads, true, INFINITE);


    //Удаляем критическую секцию
    for (int i = 0; i < PHILOSOFER_COUNTS; ++i) {
        DeleteCriticalSection(&cs[i]);
		CloseHandle(&threads[i]);
    }

	DeleteCriticalSection(&outputSection);

    return 0;

}

int left(int i) {
	return (i + (PHILOSOFER_COUNTS - 1)) % PHILOSOFER_COUNTS;
}

int right(int i) {
	return i % PHILOSOFER_COUNTS;
}


void printInSTDOUT(std::string message) {
	EnterCriticalSection(&outputSection);
	std::cout << message;
	LeaveCriticalSection(&outputSection);
}

void eat(int philId) {
	printInSTDOUT("Philosofer " + std::to_string(philId) + " is eating" + "\n" + "forks: " + std::to_string(1 + left(philId) ) + " " + std::to_string(1 + right(philId)) + "\n");
	Sleep(EATING_TIME);
}

void think(int philId) {
	printInSTDOUT("Philosofer " + std::to_string(philId) + " is thinking" + "\n");
	Sleep(THINKING_TIME);
}

DWORD WINAPI doPhilosofie(LPVOID params) {
	int* philNumberPtr = (int*)params;
	int philNumber = *philNumberPtr;

	bool isEnoungh = false;
	for (int i = 0; !isEnoungh; i++) {

		EnterCriticalSection(&cs[left(philNumber)]);
		EnterCriticalSection(&cs[right(philNumber)]);

		eat(philNumber);

		LeaveCriticalSection(&cs[left(philNumber)]);
		LeaveCriticalSection(&cs[right(philNumber)]);

		think(philNumber);

		isEnoungh = i > 10;
	}

	return 0;
}