//#include "Operations.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include "Service.h"
//
//Operation* createOperation(undoRedoFct redo, undoRedoFct undo, Offer* offer1)
//{
//	Operation* o = malloc(sizeof(Operation));
//	if (o == NULL)
//		return o;
//	o->offer = copyOffer(offer1);
//	o->undoFunction = undo;
//	o->redoFunction = redo;
//
//	return o;
//}
//
//void destroyOperation(Operation* op)
//{
//	if (op == NULL)
//		return;
//	destroyOffer(op->offer);
//	free(op);
//}
//
//OperationStack* createStack(Service* service)
//{
//	OperationStack* s = malloc(sizeof(OperationStack));
//	if (s == NULL)
//		return s;
//	s->arr = createDynamicArray(10, destroyOperation);
//	s->length = 0;
//
//}
//
//void push(Operation* o, OperationStack* s)
//{
//		s->oper[s->length] = *o;
//}
//
//void pop(Operation* o, OperationStack* s) {
//	if (strcmp(s->arr[(s->length) - 1], "remove") == 0);
//	{
//		removeOfferService(,s->oper->offer->destination,s->oper->offer->departureDate);
//	}
//}


#include "Operations.h"
#include <stdlib.h>
#include <stdio.h>

Operation* createOperation(Offer* currentOffer, char* currentAction) {
	Operation* newOperation = malloc(sizeof(Operation) * 10);
	newOperation->repo
}
