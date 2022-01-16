// Carlos Manoel Pedrosa de Oliveira - TIA: 32068549

#include <iostream>
#include "./StaticQueue.h"


StaticQueue Create()
{
	StaticQueue queue =
	{
		0,
		0,
		0,
		{ 0 }
	};

	return queue;
}

bool Enqueue(StaticQueue& queue, propriedadesAgua elem)
{
	if (queue.count == Size(queue))
	{
		return false;
	}

	queue.values[queue.rear] = elem;

	queue.rear = (queue.rear + 1) % Size(queue);

	++queue.count;

	return true;
}


propriedadesAgua Dequeue(StaticQueue& queue)
{
    propriedadesAgua vazio = {' ',0,0,0,0,0,0,0,0,0};
	if (IsEmpty(queue))
	{
		return vazio;
	}

	propriedadesAgua value = queue.values[queue.front];
	queue.values[queue.front] = vazio;


	queue.front = (queue.front + 1) % Size(queue);

	--queue.count;

	return value;
}

propriedadesAgua Front(const StaticQueue& queue)
{
	propriedadesAgua vazio = {' ',0,0,0,0,0,0,0,0,0};
	return IsEmpty(queue) ? vazio : queue.values[queue.front];
}

int Size(const StaticQueue& queue)
{
	return sizeof(queue.values) / sizeof(queue.values[0]);
}

int Count(const StaticQueue& queue)
{
	return queue.count;
}

bool IsEmpty(const StaticQueue& queue)
{
	return queue.count == 0;
}

bool Clear(StaticQueue& queue)
{
	while (!IsEmpty(queue))
	{
		Dequeue(queue);
	}

	return IsEmpty(queue);
}



