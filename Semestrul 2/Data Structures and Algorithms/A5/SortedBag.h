#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR
#include<stack>
//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	//TODO - Representation
	struct Node {
		TComp info=NULL_TCOMP;
		int left=-1;
		int right=-1;
		int frequency=1;
	};
	std::stack<Node>* minList = new std::stack<Node>;
	Node* array;
	Node root;
	Relation r;
	int nrElements;
	int firstFree;
	int capacity = 5;
	int rootIndex = -1;
public:
	//constructor
	SortedBag(Relation r);
	void resize();
	int allocateNode(TComp e);
	int returnParent(TComp e);
	//adds an element to the sorted bag
	void add(TComp e);
	void print();
	int returnRoot();
	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	int elementsWithThisFrequency(int frequency)const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const ;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};