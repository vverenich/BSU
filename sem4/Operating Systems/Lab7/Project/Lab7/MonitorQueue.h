#ifndef Monitor_h
#define Monitor_h

#include <vector>
#include <iostream>
#include <windows.h>

class MonitorQueue
{
private:
	std::vector<float> queue;
	size_t max_size;
	CRITICAL_SECTION critical_section;
	HANDLE semaphoreToAdd, semaphoreToRemove;
public:
	MonitorQueue(size_t max_size) noexcept; // nSize - ������ �����
	~MonitorQueue() noexcept;

	void AddHead(float& nElement);// ���������������������� �������
	float RemoveTail();
};

#endif