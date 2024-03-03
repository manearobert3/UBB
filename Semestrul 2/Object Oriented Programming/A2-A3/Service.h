#pragma once
#include "Repository.h"

typedef struct {
	Repository* repo;
}Service;

int verifyTypeIsSmaller( char* , char* );

TElem* sameTypeButAfterDepartureDate(Service*, char*, char*, int*);

TElem* sameTypeButAfterDepartureDateDescendingOrderByPrice(Service*, char*, char*, int*);

TElem* sameTypeButAfterDepartureDateDescendingOrderByDate(Service*, char*, char*, int*);

TElem* sameTypeOffersBiggerThanPrice(Service*, int*, int);

//void addToOperationArrayService(Service* service);
//
//void UndoOperationService(Service* service);
Offer* findOfferByDestinationAndDepartureDateServiceReturningOffer(Service* service, char* stringDestination, char* stringDepartureDate);


TElem* sameTypeOffersForUndo(Service*, int*);

Service* makeCopyService(Service* service);

void testService();

void addEntries(Service*);

Service* createService(Repository*);

void destroyService(Service*);

int verifyDepartureDate(Service*, char*, int*, int*, int*);

TElem* sameTypeOffers(Service* service, char* string, int* size);

int addOfferService(Service*, char*, char*, char*,int);

int updateOfferService(Service*, char*, char*, char*, char*, char*, int);

int verifyType(Service*, char*);

int removeOfferService(Service*, char*, char*);

int findOfferByDestinationAndDepartureDateService(Service*, char*, char*);