#pragma once
#include<iostream>

template <typename InfoType = int>

class queue
{
private:
	struct QItem {
		InfoType info;
		QItem* next;
		QItem(InfoType Ainfo) : info(Ainfo), next(NULL) {}
	};
	QItem* front, * rear;
	unsigned size;

	void Erase();
	void Clone(const queue&);
public:
	queue() :front(NULL), rear(NULL), size(0) {};
	queue(const queue&);
	~queue();
	queue& operator = (const queue&);

	void Push(InfoType AInfo);
	bool Pop();
	InfoType GetFirst() const;
	bool IsEmpty() const;
	unsigned GetSize() const;

	InfoType operator [] (unsigned) const;
	void Browse(void ItemWork(InfoType)) const;
	void Browse(void ItemWork(InfoType&));
};

