
#ifndef STACK_H_
#define STACK_H_

#pragma once
#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <vector>
#include <string>

template<class Type>
class stackEntry;

template<class Type>
class stack;


template <class Type>
class stackEntry
{
	friend class stack<Type>;

private:
	Type dataValue;
	stackEntry<Type>* pNext;

public:
	stackEntry();

protected:
	stackEntry(const Type& newData, stackEntry<Type>* newNext = nullptr);
	virtual ~stackEntry() {
	
	}
	virtual void next(stackEntry<Type>* pointer) {
		pNext = pointer;
	}
	virtual Type& data() {
		return dataValue;
	}
	virtual const Type& data() const {
		return dataValue;
	}
	virtual stackEntry<Type>* next() {
		return pNext;
	}
};

template <class Type>
class stack
{
private:
	stackEntry<Type>* topStack;
	std::size_t numEntries;

public:
	stack();
	stack(const stack& other);
	const stack& operator=(const stack& rhs);
	virtual ~stack();
	const Type& top() const {
		assert(topStack != nullptr);
		return topStack->data();
	}
	Type& top() {
		assert(topStack != nullptr);
		return topStack->data();
	}
	bool empty() const {
		return numEntries == 0;
	}
	void clear();
	std::size_t size() const {
		return numEntries;
	}
	void push(const Type& value);
	void pop();
	void debug() const;
	void debug(std::ostream& out) const;

private:
	void copyStack(const stack& other);

};

template <class Type>
stackEntry<Type>::stackEntry()
	: dataValue(), pNext(nullptr)
{

}

template <class Type>
stackEntry<Type>::stackEntry(const Type& newData, stackEntry<Type>* newNext)
	: dataValue(newData), pNext(newNext)
{
}

template <class Type>
stack<Type>::stack()
	: topStack(), numEntries(0)
{
}

template <class Type>
void stack<Type>::copyStack(const stack& other) {
	
	stackEntry<Type>* node = other.topStack;
	std::vector<Type> temp;


	while (node != nullptr) {
		temp.push_back(node->data());
		node = node->next();
		
	}
	for (auto i = temp.size()-1; i >= 0; i--) {
		push(temp.at(i));
	}
}

template <class Type>
stack<Type>::stack(const stack& other)
	: topStack(nullptr), numEntries(0)
{
	copyStack(other);
}


template<class Type>
const stack<Type>& stack<Type>::operator=(const stack& other) {
	if (this != &other) {
		clear();
		copyStack(other);
	}
	return *this;
}

template <class Type>
stack<Type>::~stack<Type>() {
	clear();
}

template <class Type>
void stack<Type>::push(const Type& value) {

	if (empty()) {
		stackEntry<Type>* node = new stackEntry<Type>(value);
		node->next(nullptr);
		topStack = node;		
		numEntries++;
	}
	else {
		stackEntry<Type>* node = new stackEntry<Type>(value);
		node->next(topStack);
		topStack = node;
		numEntries++;
	}
}

template <class Type>
void stack<Type>::pop() {

	if (!empty()) {
		stackEntry<Type>* temp = topStack->next();
		delete topStack;
		topStack = temp;
		numEntries--;
	}

}

template <class Type>
void stack<Type>::clear() {
	while (!empty()) {
		pop();
	}
}

template <class Type>
void stack<Type>::debug() const {
	debug(std::cout);
}

template <class Type>
void stack<Type>::debug(std::ostream& out) const {
	{
		out << "Number of items in stack: " << numEntries << std::endl;
		out << "Top of stack is entry @ " << topStack << std::endl;

		stackEntry<Type>* pNext = topStack;

		while (pNext != nullptr)
		{
			out << "@ " << pNext << ", next @ " << pNext->next() << ", data = " << pNext->data() << std::endl;
			pNext = pNext->next();
		}
	}
}














#endif


