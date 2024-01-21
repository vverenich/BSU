#include <iostream>
#include <windows.h>
#include <string>
#include <random>
#include <process.h>
#include "MonitorQueue.h"

struct Arg
{
	size_t products_amount;
	size_t index;
	MonitorQueue* stack;

	Arg(size_t index, size_t amount, MonitorQueue* stack) {
		this->products_amount = amount;
		this->stack = stack;
		this->index = index;
	}
};

void Producer(Arg* arg)
{
	srand(arg->index);
	for (size_t i = 0; i < arg->products_amount; ++i)
	{
		float r = (float)rand() / RAND_MAX;
		(arg->stack)->AddHead(r);
	}
}

void Consumer(Arg* arg)
{
	for (size_t i = 0; i < arg->products_amount; ++i)
	{
		(arg->stack)->RemoveTail();
	}
}

int positiveIntAsker(const std::string& message)
{
	std::string temp;
	std::cout << message;
	std::getline(std::cin, temp);
	int arg = std::atoi(temp.c_str());
	if (arg <= 0)
	{
		throw std::exception("Argument should be positive integer");
	}

	return arg;
}


int main()
{
	try
	{
		MonitorQueue queue(positiveIntAsker("Enter queue size: "));
		size_t thread_amount = positiveIntAsker("Enter thread amount: ");

		unsigned int IDThread;
		HANDLE* consumers = new HANDLE[thread_amount],
			* producers = new HANDLE[thread_amount];
		std::vector<Arg> args;
		for (size_t i = 0; i < thread_amount; ++i)
		{
			std::cout << i + 1 << ") ";
			args.push_back(Arg(i, positiveIntAsker("Enter products amount for producer and consumer: "), &queue));
			std::cout << std::endl;
		}

		for (size_t i = 0; i < thread_amount; ++i)
		{
			consumers[i] = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Consumer, &args[i], 0, &IDThread);
			producers[i] = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Producer, &args[i], 0, &IDThread);
		}

		WaitForMultipleObjects(thread_amount, consumers, TRUE, INFINITE);
		WaitForMultipleObjects(thread_amount, producers, TRUE, INFINITE);

		for (size_t i = 0; i < thread_amount; ++i)
		{
			CloseHandle(consumers[i]);
			CloseHandle(producers[i]);
		}
		delete[] consumers;
		delete[] producers;

		std::cout << "exit...\n";
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}



}