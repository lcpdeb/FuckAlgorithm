#pragma once
#include <iostream>
using namespace std;


/*
* 环形队列C++实现
*/
template <typename T>
class Queue
{
public:
	Queue(int capacity);
	virtual ~Queue(void);
	void ClearQueue(void);
	bool IsQueueEmpty(void) const;
	bool IsQueueFull(void) const;
	int GetQueueLength(void) const;
	bool EnQueue(T element);
	bool DeQueue(T& element);
	void TraverseQueue(void);
private:
	T* m_pQueue;					//队列数组指针
	T m_Head;
	int m_Tail;
	int m_QueueLength;				//队列元素个数
	int m_QueueCapacity;			//队列数组容量
};

template <typename T>
Queue<T>::Queue(int capacity)
{
	m_QueueCapacity = capacity;
	ClearQueue();
	m_pQueue = new T[m_QueueCapacity];
}

template <typename T>
Queue<T>::~Queue(void)
{
	delete m_pQueue;
	m_pQueue = nullptr;
}

template <typename T>
void Queue<T>::ClearQueue(void)
{
	m_Head = m_Tail = m_QueueLength = 0;
}

template <typename T>
bool Queue<T>::IsQueueEmpty(void) const
{
	return m_QueueLength == 0;
}

template <typename T>
bool Queue<T>::IsQueueFull(void) const
{
	return m_QueueLength == m_QueueCapacity;
}

template <typename T>
int Queue<T>::GetQueueLength(void) const
{
	return m_QueueLength;
}

template <typename T>
bool Queue<T>::EnQueue(T element)
{
	if (IsQueueFull())
	{
		cout << "Queue is full." << endl;
		return false;
	}
	else
	{
		m_pQueue[m_Tail] = element;
		m_Tail++;
		m_Tail = m_Tail % m_QueueCapacity;
		m_QueueLength++;
		return true;
	}
}

template <typename T>
bool Queue<T>::DeQueue(T& element)
{
	if (IsQueueEmpty())
	{
		cout << "Queue is empty." << endl;
		return false;
	}
	else
	{
		element = m_pQueue[m_Head];
		m_Head++;
		m_Head = m_Head % m_QueueCapacity;
		m_QueueLength--;
		return true;
	}
}

template <typename T>
void Queue<T>::TraverseQueue(void)
{
	cout << "************* Printing all elements in queue **************" << endl;
	for (int i = m_Head; i < m_QueueLength + m_Head; i++)
	{
		cout << m_pQueue[i % m_QueueCapacity] << endl;
	}
	cout << "******** Printed all elements in queue completedly ********" << endl;
}