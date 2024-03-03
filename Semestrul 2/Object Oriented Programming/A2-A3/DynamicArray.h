#pragma once

#include "offer.h"

typedef void* TElem;

typedef void (*destroyer)(TElem);

typedef struct
{
	TElem* elements;
	int capacity;
	int length;
	destroyer destroyFunction;
} DynamicArray;


DynamicArray* createDynamicArray(int capacity, destroyer destroyFunction);
void destroyDynamicArray(DynamicArray* array);
int getLength(DynamicArray* array);
TElem* get(DynamicArray* array, int pos);
void add(DynamicArray* array, TElem e);
void removeElement(DynamicArray* array, int poz);
void testDynamicArray();