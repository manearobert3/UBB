#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
    this->first();
}

void ListIterator::first(){
    // set the iterator to point to the head of the list
    this->current = this->list.head;
}

void ListIterator::next(){
    // move the iterator to the next node in the list
    if (this->valid()) {
        this->current = this->current->next;
    }
}

bool ListIterator::valid() const{
    // check if the iterator is pointing to a valid node
    return this->current != nullptr;
}

TComp ListIterator::getCurrent() const{
    // return the info stored in the node pointed to by the iterator
    if (!this->valid()) {
        throw exception();
    }
    return this->current->info;
}


