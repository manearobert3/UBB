#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>



SortedIteratedList::SortedIteratedList(Relation r) {
    this->r = r;
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

int SortedIteratedList::size() const {
    // traverse the list and count the nodes
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

bool SortedIteratedList::isEmpty() const {
    return head == nullptr;
}

ListIterator SortedIteratedList::first() const {
    ListIterator iter(*this);
    iter.current = head;
    return iter;
}

TComp SortedIteratedList::getElement(ListIterator pos) const {
    if (!pos.valid()) {
        throw exception();
    }
    // return the info stored in the node pointed to by the iterator
    return pos.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& pos) {
    if (!pos.valid()) {
        throw exception();
    }

    Node* currentNode = pos.current;

    // special case: remove the head node
    if (currentNode == head) {
        head = head->next;
        if (head == nullptr) {
            // the list became empty
            tail = nullptr;
        }
        pos.current = head;
        return currentNode->info;
        delete currentNode;
    }

    // find the node before the node to be removed
    Node* prev = head;
    while (prev->next != currentNode) {
        prev = prev->next;
    }

    // remove the current node and update the iterator
    prev->next = currentNode->next;
    if (currentNode == tail) {
        tail = prev;
    }
    delete currentNode;
    pos.current = prev->next;

    return currentNode->info;
}

ListIterator SortedIteratedList::search(TComp e) const{
    Node* current = head;
    while (current != nullptr && current->info != e) {
        current = current->next;
    }
    ListIterator iter(*this);
    iter.current = current;
    return iter;
}

void SortedIteratedList::add(TComp e) {
    // create a new node for the element
    Node* newNode = new Node;
    newNode->info = e;
    newNode->next = nullptr;

    // special case: the list is empty, insert the new node as the head
    if (head == nullptr) {
        head = newNode;
    }
    else {
        // find the node before the insertion point
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr && r(current->info, e)) {
            prev = current;
            current = current->next;
        }

        // insert the new node after the previous node or at the beginning of the list
        if (prev == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

SortedIteratedList::~SortedIteratedList() {
    // deallocate memory for all nodes
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    length = 0;
}
