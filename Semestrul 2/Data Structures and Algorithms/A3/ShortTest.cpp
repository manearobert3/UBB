#include "ShortTest.h"

#include <assert.h>
#include <exception>


#include "IteratedList.h"
#include "ListIterator.h"

#include<iostream>

using namespace std;

void printSLLA(const IteratedList& l) {
	ListIterator it = l.first();
	while (it.valid()) {
		std::cout << it.getCurrent() << ' ';
		it.next();
	}
	std::cout << std::endl;
}

bool condition1(TElem e) {
	if (e > 10) {
		return true;
	}
	return false;
}



	void testAll() {
		IteratedList list = IteratedList();
		//list.addToEnd(1);
		//list.addToEnd(12);
		//list.addToEnd(14);
		//printSLLA(list);
		//list.filter(condition1);
		printSLLA(list);
		ListIterator test = list.first();
		list.remove(test);
		test.first();
		list.remove(test);
		assert(list.size() == 0);
		assert(list.isEmpty());

		list.addToEnd(1);
		assert(list.size() == 1);
		assert(!list.isEmpty());

		ListIterator it = list.search(1);
		assert(it.valid());
		assert(it.getCurrent() == 1);
		it.next();
		assert(!it.valid());
		it.first();
		assert(it.valid());
		assert(it.getCurrent() == 1);

		assert(list.remove(it) == 1);
		assert(list.size() == 0);
		assert(list.isEmpty());
		list.addToEnd(1);
		list.addToEnd(3);
		list.addToEnd(7);
		ListIterator it3 = list.first();
		list.addToPosition(it3, 77);
		list.addToPosition(it3, 44);
		assert(list.size() == 5);
		ListIterator it2 = list.first();
		assert(it2.getCurrent() == 1);
		it2.next();
		assert(it2.getCurrent() == 77);
		it2.next();
		assert(it2.getCurrent() == 44);
		it2.next();
		assert(it2.getCurrent() == 3);
		it2.next();
		assert(it2.getCurrent() == 7);
		it2.next();
		assert(it2.valid() == false);

		IteratedList list2 = IteratedList();
		list2.addToBeginning(4);
		list2.addToEnd(5);
		list2.addToBeginning(3);
		list2.addToEnd(6);
		list2.addToBeginning(2);
		list2.addToEnd(7);
		int i = 2;
		ListIterator it4 = list2.first();
		while (it4.valid()) {
			assert(it4.getCurrent() == i);
			i++;
			it4.next();
		}
	};