#pragma once

#include "offer.h"

typedef void* TElem;

typedef void (*destroyer)(TElem);

typedef struct
{
	int* arrayOfCommands;
	TElem* elements;
	int capacity;
	int length;
	int index;
	int operationType;
	destroyer destroyFunction;
} OperationDynamicArray;

void popOperation(OperationDynamicArray* currentArray);
TElem* returnLastOperation(OperationDynamicArray * currentArray);
void addToOperationArrayUpdate(OperationDynamicArray* currentArray, TElem elementInitial, TElem elementAfterUpdate, int operationType);

OperationDynamicArray* createOperationDynamicArray(int capacity, destroyer destroyFunction);
void destroyOperationDynamicArray(OperationDynamicArray* currentArray);
int getLengthOperationDynamicArray(OperationDynamicArray* currentArray);
TElem* getOperations(OperationDynamicArray* currentArray, int pos);
void addToOperationArray(OperationDynamicArray* currentArray,TElem element, int typeOfOperation);
void removeElementOperationArray(OperationDynamicArray* currentArray, int poz);
//void testOperationDynamicArray();