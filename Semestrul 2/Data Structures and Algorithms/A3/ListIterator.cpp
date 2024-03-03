#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

ListIterator::ListIterator(const IteratedList& list) : list(list) {
	if (list.tail >= 0)
		this->current = list.head;
	else
		this->current = -1;
}
// BC:WC:AC = Theta(1)
void ListIterator::first() {
	if (list.tail >= 0)
		this->current = list.head;
	else
		this->current = -1;
}
// BC:WC:AC = Theta(1)
void ListIterator::next() {
	if (this->current == -1)
		throw std::exception();
	else
		this->current = list.elements[this->current].next;
}

// BC:WC:AC = Theta(1)

void ListIterator::prev() {
	if (this->current == -1)
		throw std::exception();
	else
		this->current = list.elements[this->current].prev;
}
// BC:WC:AC = Theta(1)
bool ListIterator::valid() const {
	if(this->current==-1)
		return  false;
	return true;
}
// BC:WC:AC = Theta(1)
TElem ListIterator::getCurrent() const {
	if (!valid())
		throw std::exception();
	else
		return list.elements[this->current].elem;
}



