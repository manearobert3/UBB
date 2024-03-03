#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;
//WC:BC:AC: Theta(capacity)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	int node = bag.rootIndex;
	int check;
	for (int i = 0; i < bag.capacity; i++) {
		freq[i] = bag.array[i].frequency;
		check = freq[i];
	}
	if (this->bag.nrElements <= 0) {
		this->current = -1;
	}
	else {
		while (node != -1) {
			/*int freq = bag.array[node].frequency;
			while (freq != 0)
			{
				this->stack.push(node);
				freq--;
			}*/
			this->stack.push(node);
			node = bag.array[node].left;
		}
		if (!this->stack.empty()) {
			this->current = stack.top();
		}
	}
}

//BC:WC:AC: Theta(1)
int SortedBagIterator::returnIt() {
	return this->current;
}
//BC:WC:AC: Theta(1)
TComp SortedBagIterator::getCurrent() {
	if (valid())
		return bag.array[this->current].info;
	else throw exception();
}

//BC:WC:AC: Theta(1)
bool SortedBagIterator::valid() {
	if (this->current != -1 and this->current < this->bag.capacity)
		return true;
	else
	return false;
}


//WC: Theta(bag.capacity), BC: Theta(1)
void SortedBagIterator::next() {
	TComp null = NULL_TCOMP;
	if (!valid())
		throw exception();
	if (freq[this->current] >= 2) {
		freq[this->current]--;
	}
	else{
	int parent = this->current;
	int node = this->stack.top();
	stack.pop();
	/*if (this->current != node && bag.array[node].frequency!=1)
	{*/
		if (bag.array[node].right != -1) {
			node = bag.array[node].right;
			while (node != -1) {
				/*int freq = bag.array[node].frequency;
				while (freq != 0)
				{
					this->stack.push(node);
					freq--;
				}*/
				this->stack.push(node);
				node = bag.array[node].left;
			}
		}
	/*}
	else */
	if (!this->stack.empty()) {
		this->current = this->stack.top();
	}
	else {
		this->current = -1;
	}
}
}

//WC:AC:BC: Theta(bag.capacity)
void SortedBagIterator::first() {
	for (int i = 0; i < bag.capacity; i++) {
		freq[i] = bag.array[i].frequency;
		int check = freq[i];
	}
	while (!this->stack.empty())
		this->stack.pop();
	int node = bag.rootIndex;
	while (node != -1) {
		int freq = bag.array[node].frequency;
		/*while (freq != 0)
		{
			this->stack.push(node);
			freq--;
		}*/
		this->stack.push(node);
		node =bag.array[node].left;
	}
	if (!this->stack.empty()) {
		this->current = this->stack.top();
	}
	else {
		this->current = -1;
	}
}

