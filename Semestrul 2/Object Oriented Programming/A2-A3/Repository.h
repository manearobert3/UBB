#pragma once
#include "DynamicArray.h"
#include "OperationDynamicArray.h"

typedef struct {
	DynamicArray* array;
	OperationDynamicArray* arrOperation;
} Repository;
int addOfferUndo(Repository* repo, Offer* newOffer);


Offer* findOfferByDestinationAndDepartureDateReturningOffer(Repository* repo, char* destination, char* departureDate);

void testRepository();

Repository* createRepo();

void addToOperationList(Repository*);

void removeFromOperationList(Repository*);

void resetRedoOperationList(Repository*);

void undoOperation(Repository*);

void destroyRepo(Repository*);

int getSize(const Repository*);

Repository* makeCopyOfRepo(Repository* );

Offer* getOfferByIndex(Repository*, int);

int addOffer(Repository*, Offer*);

int removeOffer(Repository*, Offer*);

int updateOffer(Repository*, char*, char*, Offer*);

Offer* getOffer(Repository*, char*, char*);

int findOfferByDestinationAndDepartureDate(Repository*, char*, char*);

void interchangeRemove(Repository* repo, Repository* undo, int index);

void interchangeAdd(Repository* repo, Repository* undo, int index);


void interchange(Repository* repo, Repository* undo, int index);