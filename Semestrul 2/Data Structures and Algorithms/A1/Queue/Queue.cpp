#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
	//TODO - Implementation
	this->capacity = 5;
	this->length = 0;
	this->elements = new TElem[this->capacity];
	this->front = 0;
	this->rear = -1;
	
}
/// complexity: WC: Theta(this->length);
/// BC: Theta(1);
TElem Queue::minimumElement() const {
	int minimum = 9999;
	if (isEmpty() == true) {
		throw exception();
	}
	else if (this->front < this->rear) {
		for (int index = this->front; index <= this->rear; index++)
		{
			if (this->elements[index] < minimum)
			{
				minimum = this->elements[index];
			}
		}
	}
	else if (this->front > this->rear) {
		for (int index = 0; index <= this->rear; index++)
		{
			if (this->elements[index] < minimum)
			{
				minimum = this->elements[index];
			}
		}
		for (int index = this->front; index < this->capacity; index++)
		{
			if (this->elements[index] < minimum)
			{
				minimum = this->elements[index];
			}
		}
	}
	else if (this->front == this->rear) {
		return this->elements[this->front];
	}
	return minimum;

}

//complexity:WC: Theta(this->capacity*2);
//complexity:BC: Theta(1);
void Queue::push(TElem elem) {
	//TODO - Implementation
	int oldCapacity = this->capacity;
	if (this->length+1 > this->capacity) {
		this->auxElements = new TElem[this->capacity * 2];
		for (int index = 0; index < this->capacity*2; index++) {
			this->auxElements[index] = 0;
		}
		for (int index = 0; index < this->capacity; index++) {
			this->auxElements[index] = this->elements[index];
		}
		this->elements = new TElem[this->capacity * 2];
		this->capacity = this->capacity * 2;
		for (int index = 0; index < this->capacity; index++) {
			this->elements[index] = this->auxElements[index];
		}
		int max=this->front;
		if (this->front > this->rear)
		{
			for (int index = max; index < oldCapacity; index++) {
				this->elements[oldCapacity + index] = this->elements[index];
				this->elements[index] = 0;
			}
			this->front = this->front + oldCapacity;
		}
	}
	if (this->rear + 1<this->capacity) {
		this->elements[this->rear + 1] = elem;
		this->rear++;
		this->length++;
	}
	else if (this->rear + 1 >= this->capacity) {
		this->elements[0] = elem;
		this->rear = 0;
		this->length++;
	}

	
}

//complexity: Theta(1);

TElem Queue::top() const {
	if (isEmpty() == true) {
		throw exception();
	}
	else {
		return this->elements[this->front];

	}
}
//complexity: Theta(1);

TElem Queue::pop() {
	//TODO - Implementation
	if (isEmpty() == true) {
		throw exception();
	}
	else {
		int a = this->elements[this->front];
		this->elements[this->front] = 0;
		if (this->front + 1 < this->capacity)
		{
			this->front++; 
		}
		else if(this->front+1 >= this->capacity)
		{
			this->front = 0;
		}
		this->length--;
		return a;
	}
}
//complexity: Theta(1);

bool Queue::isEmpty() const {
	if (this->length == 0) {
		return true;
	}
	else {
		return false;
	}

}


Queue::~Queue() {
	//TODO - Implementation
	delete[] this->elements;
}

