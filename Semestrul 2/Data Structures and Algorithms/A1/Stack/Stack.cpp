#include "Stack.h"
#include <exception>


using namespace std;


Stack::Stack() {
	//TODO - Implementation
	this->capacity = 5;
	this->elements = new TElem[this->capacity];
	this->length = 0;
	this->topStack = -1;
}

// complexity: WC:Theta(this->capacity*2);
// BC: Theta(1);
void Stack::push(TElem e) {
	//TODO - Implementation
	if (this->length + 1 > this->capacity) {
		this->auxElements = new TElem[this->capacity * 2];
		for (int index = 0; index < this->capacity * 2; index++) {
			this->auxElements[index] = 0;
			if (index < this->capacity)
			{
				this->auxElements[index] = this->elements[index];
			}
		}
		this->elements = new TElem[this->capacity * 2];
		for (int index = 0; index < this->capacity * 2; index++) {
			this->elements[index] = this->auxElements[index];
		}
		this->elements[this->capacity] = e;
		this->capacity = this->capacity * 2;
		this->topStack++;
		this->length++;
	}
	else if (this->length + 1 <= this->capacity)
	{
		this->topStack++;
		this->elements[this->topStack] = e;
		this->length++;
	}
}

//complexity: Theta (1)
TElem Stack::top() const {
	if (isEmpty() == true) {
		throw exception();
	}
	else {
		return this->elements[this->topStack];
	}
	return NULL_TELEM;
}

//complexity: Theta(1);
TElem Stack::pop() {
	if (isEmpty() == true) {
		throw exception();
	}
	else {
		int a = this->elements[this->topStack];
		this->elements[this->topStack] = 0;
		this->topStack--;
		this->length--;
		return a;
	}
	return NULL_TELEM;
}

//complexity: Theta(1);

bool Stack::isEmpty() const {
	if (this->length == 0) {
		return true;
	}
	else {
		return false;
	}
}

Stack::~Stack() {
	//TODO - Implementation
	delete[] this->elements;
}