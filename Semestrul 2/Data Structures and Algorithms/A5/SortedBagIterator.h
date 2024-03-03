#pragma once
#include "SortedBag.h"
#include <stack>
class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag & b);
	int current;
	int* freq=new int[bag.capacity];
	std::stack<int> stack;
	//TODO - Representation

public:
	TComp getCurrent();
	int returnIt();
	bool valid();
	void next();
	void first();
};

