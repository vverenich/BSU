#include "MonitorQueue.h"
#include <thread>

MonitorQueue::MonitorQueue(size_t max_size) noexcept
{
	if (!max_size)
		max_size = 1;
	this->max_size = max_size;

	queue = std::vector<float>();
	queue.reserve(this->max_size);

	InitializeCriticalSection(&critical_section);

	semaphoreToRemove = CreateSemaphore(NULL, 0, max_size, NULL);
	semaphoreToAdd = CreateSemaphore(NULL, max_size, max_size, NULL);
}

MonitorQueue::~MonitorQueue()
{
	CloseHandle(semaphoreToAdd);
	CloseHandle(semaphoreToRemove);
	DeleteCriticalSection(&critical_section);
}

void MonitorQueue::AddHead(float& nElement)
{
	WaitForSingleObject(semaphoreToAdd, INFINITE);
	EnterCriticalSection(&critical_section);
	queue.push_back(nElement);
	ReleaseSemaphore(semaphoreToRemove, 1, NULL);
	std::cout << "pushed " << nElement << std::endl;
	LeaveCriticalSection(&critical_section);
}

float MonitorQueue::RemoveTail()
{
	WaitForSingleObject(semaphoreToRemove, INFINITE);
	EnterCriticalSection(&critical_section);
	double last = queue.front();
	queue.erase(queue.begin());
	ReleaseSemaphore(semaphoreToAdd, 1, NULL);
	std::cout <<  "poped  " << last << std::endl;
	LeaveCriticalSection(&critical_section);

	return last;
}
