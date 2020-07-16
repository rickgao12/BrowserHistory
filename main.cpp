// Project6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "stack.h"
#include "queue.h"

void traverseQ(const int& nextItem);

int notmain()
{
	stack<int> t;
	t.push(1);
	t.push(2);
	t.push(3);
	t.debug(std::cout);

	std::cout << "copy construct" << std::endl;
	stack<int> t2 = t;
	t2.debug(std::cout);
	

	return 0;

}

void traverseQ(const int& nextItem){
	std::cout << nextItem << " " << std::endl;
}

