
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include<iostream>
IteratedList::IteratedList() {
	capacity = 10;
	head = -1;
	tail = -1;
	headfirst = -1;
	tailfirst = -1;
	elements = new DLLANode[capacity];
	firstFree = new DLLANode[capacity];
	this->firstFree[0].prev = -1;
	this->firstFree[0].next = 1;
	for (int i = 1; i < capacity-1; i++) {
		this->firstFree[i].prev = i - 1;
		this->firstFree[i].next = i+1;
	}
	this->firstFree[capacity - 1].next = -1;
	this->firstFree[capacity - 1].prev = capacity - 2;

}	
// BC: Theta(1), WC: Theta(firstFree);
void IteratedList::resize() {
	int newCapacity = capacity * 2;
	DLLANode* copy = new DLLANode[capacity];
	DLLANode* copyFirstFree = new DLLANode[capacity];
	for (int i = 0; i < capacity / 2; i++)
	{copy[i] = this->elements[i];
	copyFirstFree[i] = this->firstFree[i];
}
	copyFirstFree[capacity-1].next = capacity;
	for (int i = capacity; i < newCapacity - 1; i++) {
		copyFirstFree[i].prev = i - 1;
		copyFirstFree[i].next = i+1;
	}
	copyFirstFree[newCapacity - 1].next = -1;
	copyFirstFree[newCapacity - 1].prev = newCapacity - 2;

	delete[] this->elements;
	delete[] this->firstFree;
	this->elements = copy;
	this->firstFree = copyFirstFree;
}
// BC:WC:AC = Theta(1)
int IteratedList::size() const {
	return this->nrElems;
}
// BC:WC:AC = Theta(1)
bool IteratedList::isEmpty() const {
	if (this->nrElems == 0)
		return true;
	return false;
}
// BC:WC:AC = Theta(1)
ListIterator IteratedList::first() const {
	ListIterator iter(*this);
	iter.current = head;
	return iter;
}
// BC:WC:AC = Theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid()) {
		throw std::exception();
	}
	return pos.getCurrent();
}
// BC:WC:AC = Theta(1)
TElem IteratedList::remove(ListIterator& pos) {
	if (!pos.valid()) {
		throw std::exception();
	}
	int currentPos = pos.current;
	if (currentPos == tail && currentPos == head) {
		tail = -1;
		head = -1;
		headfirst = currentPos;
		
	}
	else if (currentPos == tail) {
		this->elements[this->elements[currentPos].prev].next = -1;

		tail = this->elements[currentPos].prev;
		int headInitial = headfirst;
		headfirst = currentPos;
		this->firstFree[headfirst].prev = -1;
		this->firstFree[headfirst].next = headInitial;
		this->firstFree[headInitial].prev = currentPos;
		
	}
	else if (currentPos == head) {
		this->elements[this->elements[currentPos].next].prev = -1;
		head = this->elements[currentPos].next;
		this->elements[currentPos].elem = this->elements[this->elements[currentPos].next].elem;
		this->elements[currentPos].next = this->elements[this->elements[currentPos].next].next;
		int headInitial = headfirst;
		headfirst = currentPos;
		this->firstFree[headfirst].prev = -1;
		this->firstFree[headfirst].next = headInitial;
		this->firstFree[headInitial].prev = currentPos;
	}
	else
	{
		this->elements[this->elements[currentPos].prev].next = this->elements[currentPos].next;
		this->elements[this->elements[currentPos].next].prev = this->elements[currentPos].prev;
		int headInitial = headfirst;
		headfirst = currentPos;
		this->firstFree[headfirst].prev = -1;
		this->firstFree[headfirst].next = headInitial;
		this->firstFree[headInitial].prev = currentPos;
	}
	nrElems--;

	pos.next();
	return this->elements[currentPos].elem;
}
// BC = Theta(1), WC = Theta(nrElems); 
ListIterator IteratedList::search(TElem e) const{
	ListIterator currentPos = first();
	while (currentPos.valid())
	{
		if (currentPos.getCurrent() == e)
			return currentPos;
		currentPos.next();
	}
	return currentPos;
}
// BC:AC:WC Theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid()) {
		throw std::exception();
	}

	int currentNode = pos.current;
	TElem oldValue = this->elements[currentNode].elem;
	this->elements[currentNode].elem = e;
	return oldValue;
}
// BC:AC:WC Theta(1)
void IteratedList::addToBeginning(TElem e) {

	if (nrElems == capacity)
	{
		resize();
	}
	if (nrElems == 0)
	{
		this->elements[headfirst].next = -1;
		this->elements[headfirst].prev = -1;
		this->elements[headfirst].elem = e;
		head = headfirst;
		tail = headfirst;
		headfirst = this->firstFree[headfirst].next;
	}
	else if (nrElems >= 1)
	{
		this->elements[head].prev = headfirst;
		this->elements[headfirst].next = head;
		this->elements[headfirst].prev = -1;
		this->elements[headfirst].elem = e;
		head = headfirst;
		headfirst = this->firstFree[headfirst].next;

	}
	
	nrElems++;
}
// BC:WC:AC Theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (nrElems == capacity)
	{
		resize();
	}
	if (!pos.valid()) {
		throw std::exception();
	}
	
	int posNode = pos.current;
	int nextNode = this->elements[posNode].next;
	if (posNode == tail) {
		this->elements[posNode].next = headfirst;
		this->elements[headfirst].next = -1;
		this->elements[headfirst].prev = posNode;
		this->elements[headfirst].elem = e;
		tail = headfirst;
		headfirst = this->firstFree[headfirst].next;
	}
	else {
		this->elements[posNode].next = headfirst;
		this->elements[headfirst].next = nextNode;
		this->elements[headfirst].prev = posNode;
		this->elements[headfirst].elem = e;
		this->elements[nextNode].prev = headfirst;
		headfirst = this->firstFree[headfirst].next;
	}
	pos.current = this->firstFree[headfirst].prev;
	nrElems++;
}
// BC:WC:AC = Theta(1)
void IteratedList::addToEnd(TElem e) {
	if (nrElems == capacity)
	{
		resize();
	}
	/*this->elements[firstFree].elem = e;
	this->elements[firstFree].prev = -1;
	this->elements[firstFree].next = head;
	this->elements[head].prev = firstFree;
	head = firstFree;*/
	if (nrElems == 0)
	{
		this->elements[headfirst].next = -1;
		this->elements[headfirst].prev = -1;
		this->elements[headfirst].elem = e;
		tail = -1;
		head = -1;
		headfirst = this->firstFree[headfirst].next;
	}
	else if (nrElems >= 1)
	{
		this->elements[tail].next = headfirst;
		this->elements[headfirst].next = -1;
		this->elements[headfirst].prev = tail;
		this->elements[headfirst].elem = e;
		tail = headfirst;
		headfirst=this->firstFree[headfirst].next;
		

	}
	firstFree++;
	nrElems++;
}

void IteratedList::filter(Condition cond)
{
	ListIterator position = first();
	int currentPos = position.current;
	while (position.valid()) {
		if (!cond(position.getCurrent())) {
			if (currentPos == head && currentPos == tail)
			{
				head = -1;
				tail = -1;

			}
			else if (currentPos == head)
			{
				this->elements[this->elements[currentPos].next].prev = -1;
				head = this->elements[currentPos].next;
			}
			else if (currentPos == tail) {
				this->elements[this->elements[currentPos].prev].next = -1;
				tail = this->elements[currentPos].prev;
			}
			else
			{
				currentPos = position.current;
				this->elements[this->elements[currentPos].prev].next = this->elements[currentPos].next;
				this->elements[this->elements[currentPos].next].prev = this->elements[currentPos].prev;
			}
			capacity--;
			nrElems--;
		}
	
		position.next();
	}
}


IteratedList::~IteratedList() {
	delete[] this->elements;
}
