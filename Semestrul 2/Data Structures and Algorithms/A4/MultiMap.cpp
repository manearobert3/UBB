#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


int MultiMap::testHash(TKey key)
{
	return hashFunction(key);
}


int MultiMap::returnCap() {
	return this->capacity;
}

//WC:BC:AC: Theta(capacity)
MultiMap::MultiMap() {
	//TODO - Implementation
	this->capacity = 5;
	next = new int[this->capacity];
	elements = new TElem[this->capacity];
	nrElements = 0;
	firstFree = 0;
	for (int i = 0; i < this->capacity; i++) {
		next[i] = -1;
		elements[i] = NULL_TELEM;
	}
}

void MultiMap::print() {
	for (int i = 0; i < this->capacity; i++) {
		std::cout << i<<":element: " << elements[i].first << ", " << elements[i].second << ", next: " << next[i] << std::endl;
	}
}
//BC:Theta(1), WC: Theta(capacity)
void MultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	if (nrElements + 1 > this->capacity)
		resize();
	nrElements++;
	int i = 0;
	int currentPosition;
	int previous=0;
	int hashPosition = hashFunction(c);
	if (elements[hashPosition] == NULL_TELEM) {
		elements[hashPosition].first = c;
		elements[hashPosition].second = v;
	}
	else {
		currentPosition = hashPosition;
		previous = currentPosition;
		/*for (i = 0; i < this->capacity; i++) {
			if (elements[i] == NULL_TELEM and next[i] == -1) {
				firstFree = i;
				break;
			}
		}*/
		for (i = this->capacity-1; i >=0; i--) {
			if (elements[i] == NULL_TELEM and next[i] == -1) {
				firstFree = i;
				break;
			}
		}
		elements[firstFree].first = c;
		elements[firstFree].second = v;
		while (next[currentPosition] != -1)
		{
			currentPosition = next[currentPosition];
		}
		next[currentPosition] = firstFree;

	}
	
}
//BC:AC:WC: Theta(capacity)
void MultiMap::resize()
{	
	int oldCapacity = capacity;
	capacity = capacity * 2;
	TElem* newElements = new TElem[capacity];
	int* newNext = new int[capacity];
	int newPosition;
	int newFirstFree=0;
	TElem element;
	for (int i = 0; i < capacity; i++) {
		newNext[i] = -1;
		newElements[i]= NULL_TELEM;
	}
	for (int i = 0; i < oldCapacity; i++) {
		if (elements[i] != NULL_TELEM)
		{
			element = elements[i];
			newPosition = hashFunction(elements[i].first);
			if (newElements[newPosition] == NULL_TELEM)
				newElements[newPosition] = element;
			else {
				while (newNext[newPosition] != -1)
					newPosition = newNext[newPosition];
				/*for (int j = 0; j < capacity; j++) {
					if (newElements[j] == NULL_TELEM and newNext[j] == -1) {
						newFirstFree = j;
						break;
					}
				}*/
				for (int j = capacity-1; j >=0; j--) {
					if (newElements[j] == NULL_TELEM and newNext[j] == -1) {
						newFirstFree = j;
						break;
					}
				}
				newNext[newPosition] = newFirstFree;
				newElements[newFirstFree] = element;
			}
		}
	}
	delete[] elements;
	delete[] next;
	elements = newElements;
	next = newNext;
}

//BC: Theta(1), WC:Theta(number of elements that hash to the same key as the element we're trying to remove)
bool MultiMap::remove(TKey c, TValue v) {
	/*int currentPosition = hashFunction(c);
	int previous = -1;
	int p, pp;
	while (currentPosition != -1 and elements[currentPosition].second != v)
	{
		previous = currentPosition;
		currentPosition = next[currentPosition];
	}
	if (currentPosition == -1) {
		return false;
	}
	else
	{
		bool over = false;
		do
		{
			p = next[currentPosition];
			pp = currentPosition;
			while (p != -1 and hashFunction(elements[p].first)!=currentPosition) {
				pp = p;
				p = next[p];
			}
			if (p == -1) {
				over = true;
			}
			else
			{
				elements[currentPosition].first = elements[p].first;
				elements[currentPosition].second = elements[p].second;
				previous = pp;
				currentPosition = p;
			}
		} while (over==false);
	
	}
	if (previous == -1)
	{
		int idx = 0;
		while (idx < capacity and previous == -1) {
			if (next[idx] == currentPosition)
				previous = idx;
			else
				idx = idx + 1;
		}
	}
	if (previous != -1)
		next[previous] = next[currentPosition];
	elements[currentPosition] = NULL_TELEM;
	next[currentPosition] = -1;
	nrElements--;

	return true;*/


	//TODO - Implementation
	int currentPosition = hashFunction(c);
	bool found = false;
	int previous;
	if (searchFunction(c,v) == false)
		return false;
	if (elements[currentPosition] == NULL_TELEM and next[currentPosition] == -1)
		return false;
	nrElements--;
	if (elements[currentPosition].second == v and elements[currentPosition].first == c)
	{
		if (next[currentPosition] == -1) {
			elements[currentPosition] = NULL_TELEM;
			//nrElements--;
			//return true;
		}
		else {
			while (next[currentPosition] != -1) {
				elements[currentPosition] = elements[next[currentPosition]];
				previous = currentPosition;
				currentPosition = next[currentPosition];
			}
			elements[currentPosition] = NULL_TELEM;
			next[currentPosition] = -1;
			next[previous] = -1;
			//nrElements--;
			//return true;
		}
	}
	else {
		previous = currentPosition;
		currentPosition = next[currentPosition];
		while (currentPosition != -1)
		{
			if (elements[currentPosition].second == v and elements[currentPosition].first == c) {
				next[previous] = next[currentPosition];
				elements[currentPosition] = NULL_TELEM;
				next[currentPosition] = -1;
				//nrElements--;
				//return true;
			}
			previous = currentPosition;	
			currentPosition = next[currentPosition];
		}
		//return false;
	}

	return true;
}
int MultiMap::hashFunction(TKey value) const
{
	value = abs(value);
	while (value < 0)
		value = value + this->capacity;
	return value % this->capacity;
}

//BC:Theta(1), WC:Theta(number of elements that hash to the same key as the element we're trying to remove)
bool MultiMap::searchFunction(TKey c, TValue v) {
	int currentPosition;
	currentPosition = hashFunction(c);
	if (elements[currentPosition] == NULL_TELEM and next[currentPosition] == -1)
		return false;
	/*if (elements[currentPosition] != NULL_TELEM and next[currentPosition] == -1 and elements[currentPosition].first==c) {
			keyElements.push_back(elements[currentPosition].second);
		return keyElements;
	}
	while (elements[currentPosition] != NULL_TELEM and next[currentPosition] != -1)
		{	if(elements[currentPosition].first==c)
			keyElements.push_back(elements[currentPosition].second);
			currentPosition = next[currentPosition];
		}
	if(elements[currentPosition] != NULL_TELEM and next[currentPosition] == -1 and elements[currentPosition].first==c)
			keyElements.push_back(elements[currentPosition].second);*/

	while (currentPosition != -1) {
		if (elements[currentPosition].first == c and elements[currentPosition].second==v) {
			return true;
		}
		currentPosition = next[currentPosition];
	}

	return false;
}

//BC:Theta(1), WC:Theta(number of elements that hash to the same key as the element we're trying to remove)
vector<TValue> MultiMap::search(TKey c) const { 
	TKey key = c;
	vector<TValue> keyElements;
	int currentPosition;
	currentPosition = hashFunction(key);
	if (elements[currentPosition] == NULL_TELEM and next[currentPosition] == -1)
		return keyElements;
	/*if (elements[currentPosition] != NULL_TELEM and next[currentPosition] == -1 and elements[currentPosition].first==c) {
			keyElements.push_back(elements[currentPosition].second);
		return keyElements;
	}
	while (elements[currentPosition] != NULL_TELEM and next[currentPosition] != -1)
		{	if(elements[currentPosition].first==c)
			keyElements.push_back(elements[currentPosition].second);
			currentPosition = next[currentPosition];
		}
	if(elements[currentPosition] != NULL_TELEM and next[currentPosition] == -1 and elements[currentPosition].first==c)
			keyElements.push_back(elements[currentPosition].second);*/
	
	while (currentPosition != -1) {
		if (elements[currentPosition].first == c) {
			keyElements.push_back(elements[currentPosition].second);
		}
		currentPosition = next[currentPosition];
	}

	return keyElements;
}

//BC:AC:WC: Theta(1)
int MultiMap::size() const {
	return nrElements;
}

//BC:AC:WC: Theta(1)
bool MultiMap::isEmpty() const {
	if (nrElements == 0)
		return true;
	else
		return false;
}
//BC:AC:WC: Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

TKey MultiMap::minKey() const {
	TKey min = 111111;
	if (isEmpty())
		return NULL_TKEY;
	for (int i = 0; i < this->capacity; i++)
	{
		if (elements[i]!=NULL_TELEM and elements[i].first < min) {
			min = elements[i].first;
		}
	}
	return min;
}



MultiMap::~MultiMap() {
	delete[] elements;
	delete[] next;
}

