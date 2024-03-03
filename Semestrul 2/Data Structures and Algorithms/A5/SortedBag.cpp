#include "SortedBag.h"
#include "SortedBagIterator.h"
#include<iostream>
SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->r = r;
	array = new Node[capacity];
	TComp null = NULL_TCOMP;
	firstFree = 0;
	nrElements = 0;
}

void SortedBag::print() {
	for (int i = 0; i < this->capacity; i++)
		std::cout << array[i].info<<", frequency:"<<array[i].frequency<<", left"<<array[i].left<<", right:"<<array[i].right<<std::endl;
	std::cout << std::endl;
}

//BC: Theta(1), WC: Theta(capacity)
int SortedBag::allocateNode(TComp e) {
	Node newNode;
	TComp null=NULL_TCOMP;
	for (int i = 0; i < capacity; i++) {
		if (array[i].info == null)
		{
			array[i].info = e;
			return i;
		}
	}
}
//BC:Theta(1), WC: Theta(nr of parents of node)
int SortedBag::returnParent(TComp e)
{
	int currentIndex = rootIndex;
	int indexParent = -1;
	if (array[currentIndex].info == e) {
		return -1;
	}
	while (currentIndex != -1 && array[currentIndex].info != e) {
		if (r(e, array[currentIndex].info)) {
			indexParent = currentIndex;
			currentIndex = array[currentIndex].left;
		}
		else
		{		indexParent = currentIndex;
			currentIndex = array[currentIndex].right;
	}
	}
	return indexParent;
}

//BC:WC:AC: Theta(capacity)
void SortedBag::resize() {
	int oldCapacity = capacity;
	capacity = capacity * 2;
	Node* newArray = new Node[capacity];
	for (int i = 0; i < oldCapacity; i++) {
		newArray[i] = array[i];
	}
	delete[] array;
	array = new Node[capacity];
	for (int i = 0; i < capacity; i++) {
		array[i] = newArray[i];
	}
}
//BC:Theta (1), WC: Theta(nrElements)
void SortedBag::add(TComp e) {
	nrElements++;
	if (nrElements > this->capacity) {
		resize();
	}
	TComp null = NULL_TCOMP;
	if (rootIndex == -1) {
		rootIndex = allocateNode(e);
		return;
	}
	int currentIndex = rootIndex;
	while (true) {
		if (e == array[currentIndex].info) {
			array[currentIndex].frequency++;
			break;
		}
		else if (r(e, array[currentIndex].info)) {
			if (array[currentIndex].left == -1) {
				int newIndex = allocateNode(e);
				array[currentIndex].left = newIndex;
				break;
			}
			else
				currentIndex = array[currentIndex].left;
		}
		else if (!r(e, array[currentIndex].info)) {
			if (array[currentIndex].right == -1) {
				int newIndex = allocateNode(e);
				array[currentIndex].right = newIndex;
				break;
			}
			else
				currentIndex = array[currentIndex].right;
		}
		}
}

//BC:AC:WC: Theta(1)
int SortedBag::returnRoot() {
	return rootIndex;
}


//BC: Theta(1), WC: Theta(capacity)
bool SortedBag::remove(TComp e) {
	TComp null = NULL_TCOMP;
	int currentIndex = rootIndex;
	int parent;
	int verifyRootIndex;
	bool verifyRoot=false;
	if (search(e) == false)
		return false;
	while (true) {
		if (e == array[currentIndex].info) 
		{
			if (array[currentIndex].frequency > 1)
			{
				array[currentIndex].frequency--;
				nrElements--;
				return true;
		}
			if (rootIndex == currentIndex)
			{
				verifyRootIndex = currentIndex;
				verifyRoot = true;
			}
			if (array[currentIndex].left == -1 and array[currentIndex].right == -1)
			{
				parent = returnParent(e);
				if(parent!=-1){
				if (array[parent].left == currentIndex) {
					array[parent].left = -1;
				}
				else
					array[parent].right = -1;
			}
				array[currentIndex].info = NULL_TCOMP;
				array[currentIndex].left = -1;
				array[currentIndex].right = -1;
				array[currentIndex].frequency = 1;
				nrElements--;
				if (verifyRoot == true)
				{
					rootIndex = verifyRootIndex;
					root = array[verifyRootIndex];
				}
				return true;
			}
			else if ((array[currentIndex].left != -1 and array[currentIndex].right == -1) or (array[currentIndex].right != -1 and array[currentIndex].left == -1))
			{
				int indexToAppend;
				if (verifyRoot == false) {
					if (array[currentIndex].left != -1)
						indexToAppend = array[currentIndex].left;
					else
						indexToAppend = array[currentIndex].right;
					parent = returnParent(e);
					if (array[parent].left == currentIndex) {
						array[parent].left = indexToAppend;
					}
					else
						array[parent].right = indexToAppend;
					array[currentIndex].info = NULL_TCOMP;
					array[currentIndex].left = -1;
					array[currentIndex].right = -1;
					array[currentIndex].frequency = 1;
				}
				else {
					if (array[currentIndex].left != -1)
						indexToAppend = array[currentIndex].left;
					else
						indexToAppend = array[currentIndex].right;
					array[currentIndex].frequency = array[indexToAppend].frequency;
					array[currentIndex].info = array[indexToAppend].info;
					array[currentIndex].right = array[indexToAppend].right;
					array[currentIndex].left = array[indexToAppend].left;

				}
				nrElements--;
				return true;
			}
			else if ((array[currentIndex].left != -1 and array[currentIndex].right != -1))
			{
				int parent;
				int toRemoveIndex = currentIndex;
				currentIndex = array[currentIndex].right;
				while (array[currentIndex].left != -1) {
					currentIndex = array[currentIndex].left;
				}
				parent=returnParent(array[currentIndex].info);
				if (parent != -1)
				{
					if (array[parent].left == currentIndex) {
						if(array[currentIndex].right!=-1)
						array[parent].left = array[currentIndex].right;
						else
							array[parent].left = array[currentIndex].left;
					}
					else
					{
						if (array[currentIndex].right != -1)
							array[parent].right = array[currentIndex].right;
						else
							array[parent].right= array[currentIndex].left;
					}
				}
				//array[parent].right = array[currentIndex].right;
				//array[parent].left = array[currentIndex].left;
				//array[currentIndex].left=
				array[toRemoveIndex].info = array[currentIndex].info;
				array[toRemoveIndex].frequency = array[currentIndex].frequency;
				//array[toRemoveIndex].left = array[currentIndex].left;
				//array[toRemoveIndex].right = array[currentIndex].right;
				array[currentIndex].info = NULL_TCOMP;
				array[currentIndex].frequency = 1;
				array[currentIndex].left = -1;
				array[currentIndex].right = -1;
				nrElements--;
				if (verifyRoot == true)
				{
					rootIndex = verifyRootIndex;
					root = array[verifyRootIndex];
				}
				return true;
			}
		}
		else if (r(e, array[currentIndex].info)) {
			currentIndex = array[currentIndex].left;
		}
		else if (!r(e, array[currentIndex].info)) {
			currentIndex = array[currentIndex].right;
		}
		if (currentIndex == -1)
			return false;

	}
	return false;
}

//BC: Theta(1), WC: Theta(capacity)
bool SortedBag::search(TComp elem) const {	
	TComp null = NULL_TCOMP;
	int currentIndex = rootIndex;
	if (rootIndex == -1)
		return false;
	while (true) {
		if (elem == array[currentIndex].info) {
			return true;
			break;
		}
		else if (r(elem, array[currentIndex].info)) {
				currentIndex = array[currentIndex].left;
		}
		else if (!r(elem, array[currentIndex].info)) {
				currentIndex = array[currentIndex].right;
		}
		if (currentIndex == -1)
			return false;

	}
}


//BC: Theta(1), WC: Theta(capacity), AC: Theta(nr parents of specific node);
int SortedBag::nrOccurrences(TComp elem) const {
	TComp null = NULL_TCOMP;
	int currentIndex = rootIndex;
	if (rootIndex == -1)
		return 0;
	while (true) {
		if (elem == array[currentIndex].info) {
			return array[currentIndex].frequency;
			break;
		}
		else if (r(elem, array[currentIndex].info)) {
			currentIndex = array[currentIndex].left;
		}
		else if (!r(elem, array[currentIndex].info)) {
			currentIndex = array[currentIndex].right;
		}
		if (currentIndex == -1)
			return 0;

	}
}


//AC:BC:WC: Theta(1)
int SortedBag::size() const {
	//TODO - Implementation
	return nrElements;
}

int SortedBag::elementsWithThisFrequency(int frequency) const
{
	TComp null = NULL_TCOMP;
	int contor = 0;
	if (frequency <= 0)
		throw std::exception();
	for (int i = 0; i < this->capacity; i++) {	
		if (array[i].info != null and array[i].frequency == frequency) {
			contor++;
		}
	}
	return contor;
}

//AC:BC:WC: Theta(1)
bool SortedBag::isEmpty() const {
	if (nrElements == 0)
		return true;
	else
	return false;
}

//AC:BC:WC: Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete[] array;
}
