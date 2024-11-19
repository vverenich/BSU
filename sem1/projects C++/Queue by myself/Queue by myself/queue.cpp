#include "queue.h"

template<typename InfoType>
void queue <InfoType>::Erase()
{
	while (Pop());
	size = 0;
}

template<typename InfoType>
void queue<InfoType>::Clone(const queue& Q)
{
	//for (unsigned i = 0; i<Q.size; ++i)
	//Push(Q[i]);
	QItem* tmp = front;
	for (unsigned i = 0; i < Q.size; ++i) {
		Push(tmp->info);
		tmp = tmp->next;
	}
}

template<typename InfoType>
queue<InfoType>::queue(const queue&)
{
	size = 0; Clone(Q);
}

template<typename InfoType>
queue<InfoType>::~queue()
{
	Erase();
}

template<typename InfoType>
queue& queue<InfoType>::operator=(const queue& Q)
{
	if (this != &Q) {
		Erase();
		Clone(Q);
	}
	return *this;
}

template<typename InfoType>
void queue<InfoType>::Push(InfoType AInfo)
{
	QItem* tmp = new QItem(Ainfo);
	if (size > 0) {
		rear->next = tmp;
	}
	else {
		front = tmp;
	}
	rear = tmp;
	++size;
}

template <typename InfoType>
bool queue <InfoType>::Pop()
{
	if (size == 0) {
		return false;
	}
	QItem* tmp = front;
	front = front->next;
	delete tmp;
	size--;
	if (size == 0) {
		rear = NULL;
	}
	return true;
}

template<typename InfoType>
InfoType queue<InfoType>::GetFirst() const
{
	return InfoType();
}
