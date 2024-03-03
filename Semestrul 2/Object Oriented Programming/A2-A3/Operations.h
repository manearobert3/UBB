//#pragma once
//#include "offer.h"
//#include "Repository.h"
//
//typedef void (*undoRedoFct)(Repository*, Offer*);
//
//typedef struct
//{
//	undoRedoFct undoFunction;
//	undoRedoFct redoFunction;
//	Offer* offer;
//} Operation;
//
//Operation* createOperation(undoRedoFct redo, undoRedoFct undo, Offer* o);
//void destroyOperation(Operation* op);
//
//typedef struct
//{
//	DynamicArray* arr;
//	int length;
//	Operation* oper;
//} OperationStack;
//
//OperationStack* createStack(Service* service);
//// TO DO
////void destroyStack(OperationStack* s);
////void push(OperationStack* s, Operation* o);
////Operation* pop(OperationStack* s);
////int isEmpty(OperationStack* s);
//
#pragma once
#include "Repository.h"
typedef struct {
	Repository* repo;
	void* data;
	char* operationType;
}Operation;

Operation* createOperation(Offer* o, char* operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
Offer* getPlanet(Operation* o);