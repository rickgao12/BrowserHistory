/*
 * queue.h
 *
 *  Created on: Apr 17, 2019
 *      Author: dgv130030
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <vector>
#include <string>
template <class Type>
class queue;

template <class Type>
class queueEntry
{
	friend class queue<Type>;

protected:
	Type dataValue;
	queueEntry<Type>* pNext;

	queueEntry(const Type& newData, queueEntry<Type>* newNext = nullptr);
	virtual ~queueEntry();
	virtual void next(queueEntry<Type>* pointer) {
		pNext = pointer;
	}
	virtual queueEntry<Type>* next() {
		return pNext;
	}
	virtual Type& data() {
		return dataValue;
	}
	virtual const Type& data() const {
		return dataValue;
	}
};

template <class Type>
class queue
{

private:
	queueEntry<Type>* pFront;
	queueEntry<Type>* pEnd;
	std::size_t count;
public:
	queue();
	virtual ~queue();
	queue(const queue& other);
	const queue& operator=(const queue& rhs);
	const Type& front() const {
		assert(pFront != nullptr);
		return pFront->data();
	}
	Type& front() {
		assert(pFront != nullptr);
		return pFront->data();
	}
	const Type& back() const {
		assert(pEnd != nullptr);
		return pEnd->data();
	}
	Type& back() {
		assert(pEnd != nullptr);
		return pEnd->data();
	}
	bool empty() const {
		return count == 0;
	}
	std::size_t size() const {
		return count;
	}
	void push(const Type& value);
	void pop();
	void clear();
	void debug() const;
	void debug(std::ostream& out) const;
	// used by applications using the queue to work with all
	//  of the items in the queue from end to front.
	void traverse(void (*applicationFunction) (const Type& nextItem));

private:
	void copyHelper(const queue& node);
};

template <class Type>
queueEntry<Type>::queueEntry(const Type& newData, queueEntry<Type>* newNext) 
	: dataValue(newData), pNext(newNext)
{
}


template <class Type>
queueEntry<Type>::~queueEntry()
{
	
}

template <class Type>
queue<Type>::queue()
	: pFront(nullptr), pEnd(nullptr), count(0)
{
}


template <class Type>
queue<Type>::~queue()
{
	clear();
}

template <class Type>
void queue<Type>::copyHelper(const queue& other) {

	queueEntry<Type>* node = other.pFront;
	
	while (node != nullptr) {		
		push(node->data());
		node = node->next();

	}
	
}

template <class Type>
queue<Type>::queue(const queue& other)
	: pFront(nullptr), pEnd(nullptr), count(0)
{
	copyHelper(other);
}

template <class Type>
const queue<Type>& queue<Type>::operator=(const queue& rhs) {
	if (this != &rhs) {
		clear();
		copyHelper(rhs);
	}
	return *this;
}

template <class Type>
void queue<Type>::push(const Type& value) {
	if (empty()) {
		queueEntry<Type>* node = new queueEntry<Type>(value);
		node->next(nullptr);
		pFront = node;
		pEnd = node;
		count++;
	}
	else {
		queueEntry<Type>* node = new queueEntry<Type>(value);
		node->next(nullptr);
		pEnd->next(node);
		pEnd = node;
		count++;
	}
}

template <class Type>
void queue<Type>::pop() {

	if (!empty()) {
		if (pFront->next() == nullptr) {
			delete pFront;
			pFront = nullptr;
			pEnd = nullptr;
			count--;
		}
		else {
			queueEntry<Type>* temp = pFront->next();
			delete pFront;
			pFront = temp;
			count--;
		}
	}

}

template <class Type>
void queue<Type>::clear() {
	while(!empty()){
		pop();
	}
}


template<class Type>
void queue<Type>::debug() const
{
	debug(std::cout);
}

template<class Type>
void queue<Type>::debug(std::ostream& out) const
{
	{
		out << "Number of items in queue: " << count << std::endl;
		out << "Front of queue is entry @" << pFront << std::endl;
		out << "End of queue is entry @" << pEnd << std::endl;
		out << std::endl;

		queueEntry<Type>* pNext = pFront;

		while (pNext != nullptr)
		{
			out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
			pNext = pNext->next();
		}
		out << std::endl;
	}
}

template <class Type>
void queue<Type>::traverse(void (*applicationFunction) (const Type& nextItem)) {
	queueEntry<Type>* node = pFront;
	while (node != nullptr) {
		applicationFunction(node->data());
		node = node->next();
	}
}

#endif /* QUEUE_H_ */
