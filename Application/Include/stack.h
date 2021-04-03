#pragma once
#include <iostream>
using namespace std;

typedef enum DIRECTION_ {
	FROM_TOP_TO_BUTTOM = 0,
	FROM_BUTTOM_TO_TOP = 1,
}DIRECTION;

template <typename T>
class Stack
{
public:
	Stack(int size);
	~Stack(void);
	void ClearStack(void);
	bool IsStackEmpty(void);
	bool IsStackFull(void);
	int GetStackLength(void);
	bool push(T element);
	bool pop(T& element);
	void TraverseStack(DIRECTION direction);

private:
	T* m_pBuffer;
	int m_Size;
	int m_Top;
};

template <typename T>
Stack<T>::Stack(int size)
{
	m_Size = size;
	m_Buffer = new T[size];
	m_Top = 0;
}

template <typename T>
Stack<T>::~Stack(void)
{
	m_Size = 0;
	m_Top = 0;
	delete[]m_pBuffer;
}

template <typename T>
void Stack<T>::ClearStack(void)
{
	m_Top = 0;
}

template <typename T>
bool Stack<T>::IsStackEmpty(void)
{
	return 0 == m_Top;
}

template <typename T>
bool Stack<T>::IsStackFull(void)
{
	return m_Size == m_Top;
}

template <typename T>
int Stack<T>::GetStackLength(void)
{
	return m_Top;
}

template <typename T>
bool Stack<T>::push(T element)
{
	if (IsStackFull()) {
		cout << "Stack is Full;" << endl;
		return false;
	}
	else {
		m_pBuffer[m_Top] = element;
		m_Top++;
		return true;
	}
}

template <typename T>
bool Stack<T>::pop(T &element)
{
	if (IsStackEmpty()) {
		cout << "Stack is Empty;" << endl;
		return false;
	}
	else {
		m_Top--;
		element = m_pBuffer[m_Top];
		return true;
	}
}

template <typename T>
void Stack<T>::TraverseStack(DIRECTION direction)
{
	cout << "************* Printing all elements in stack **************" << endl;
	if (FROM_BUTTOM_TO_TOP == direction) {
		for (int i = 0; i < m_Top; i++)
		{
			cout << m_pBuffer[i];
		}
	}
	else {
		for (int i = m_Top; i >=; i--)
		{
			cout << m_pBuffer[i];
		}
	}
	cout << "******** Printed all elements in stack completedly ********" << endl;
}