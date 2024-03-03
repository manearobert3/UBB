#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

//ADT  SortedList (interface  with TPozition  =  Iterator-IteratedList)
// –using  a  SLL  where elements are ordered based on a relation.

int main(){
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}