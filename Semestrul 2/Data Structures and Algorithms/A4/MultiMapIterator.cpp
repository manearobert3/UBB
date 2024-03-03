#include "MultiMapIterator.h"
#include "MultiMap.h"

//WC:BC:AC Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	if (this->col.nrElements == 0 /*or col.elements[0] == NULL_TELEM*/)
		this->current = -1;
	else
	{
		first();
	}
}

//WC:BC:AC Theta(1)
int MultiMapIterator::returnIt()
{
	return this->current;
}
//WC:BC:AC Theta(1)
TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (this->valid())
		return this->col.elements[current];
	else throw exception();
}
//WC:BC:AC Theta(1)
bool MultiMapIterator::valid() const {
	if (this->current != -1 and this->current < this->col.capacity and this->current>=0)
		return true;
	else
		return false;
}
//WC:Theta(capacity), BC:Theta(1)
void MultiMapIterator::next() {
	if (this->col.nrElements > 0)
	{
		if (this->col.elements[this->current + 1] != NULL_TELEM and this->current != -1)
			this->current = this->current + 1;
		else if (this->col.elements[this->current + 1] == NULL_TELEM and this->current + 1 < this->col.capacity and this->current != -1)
		{
			this->current = this->current + 1;
			while (this->current < this->col.capacity and this->col.elements[this->current] == NULL_TELEM and this->current != -1)
				this->current++;
		}
	}
	else throw exception();
}
//WC:Theta(capacity), BC: Theta(1)
void MultiMapIterator::first() {
	for (int i = 0; i < this->col.capacity; i++) {
		if (col.elements[i] != NULL_TELEM)
		{
			this->current = i;
			break;
		}
	}
}

