#pragma once
#include "DynamicArray.h"
#include "Operations.h"

typedef struct {
	DynamicArray* array; //array of structures Operation
} OperationsStack;

// create, destroy

void push(OperationsStack*, Operation*);
Operation* pop(OperationsStack*);
int isEmpty(OperationsStack*);

