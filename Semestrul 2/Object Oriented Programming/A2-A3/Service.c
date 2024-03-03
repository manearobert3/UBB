#include "Service.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "OperationDynamicArray.h"

Service* createService(Repository* repo) {
	Service* newService = malloc(sizeof(Service));
	if (newService == NULL)
		return newService;
	newService->repo = repo;
	return newService;
}


Service* makeCopyService(Service* service) {
	return makeCopyOfRepo(service->repo);
}


//Function to destroy the Service

void destroyService(Service* service) {
	destroyRepository(service->repo);
	free(service);

}

//void addToOperationArrayService(Service* service)
//{
//	addToOperationList(service->repo);
//
//}
//
//void UndoOperationService(Service* service) {
//	undoOperation(service->repo);
//}

//Function verifies if the type is one of "seaside", "mountain" or "citybreak"
int verifyType(Service* service, char* type) {
	if (strcmp(type, "seaside") == 0 || strcmp(type, "mountain") == 0 || strcmp(type, "citybreak") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
// Verifies if a date is valid and can be used in further functions
// takes as input the string and by using sscanf puts the value between "/"
// in the corresponding integer variable
int verifyDepartureDate(Service* service, char* departureDate, int* day, int* month, int* year) {
	int dayInput, monthInput, yearInput;
	if (sscanf(departureDate, "%d/%d/%d", &dayInput, &monthInput, &yearInput) != 3) {
		return 0;
	}
	if (dayInput <1 || dayInput>31 || monthInput <1 || monthInput >12 || yearInput <1) {
		return 0;
	}
	if (monthInput ==4 || monthInput ==6 || monthInput == 9 || monthInput == 11) {
		if (dayInput > 30) {
			return 0;
		}
	}
	else if (monthInput == 2) {
		if ((yearInput %4 ==0 && yearInput %100!=0) || yearInput % 400 == 0) {
			if (dayInput >29) {
				return 0;
			}
		}
		else {
			if (dayInput > 28) {
				return 0;
			}
		}
	}
	*day = dayInput;
	*month = monthInput;
	*year = yearInput;
	return 1;
}
// Function takes as input size which will be the exact length of the elements contained
// in the offers array, and price1 is the price which is gonna be compared with
// the current price of the current Offer in the array;
TElem* sameTypeOffersBiggerThanPrice(Service* service, int* size,int price1) {
	TElem* offers = malloc(sizeof(TElem) * 100);
	*size = 0;
	for (int i = 0; i < getSize(service->repo); i++) {
		Offer* current = service->repo->array->elements[i];
		if (current->price > price1 ) {
			offers[(*size)++] = service->repo->array->elements[i];
		}
	}
	return offers;

}


TElem* sameTypeOffersForUndo(Service* service, int* size) {
	TElem* offers = malloc(sizeof(TElem) * 100);
	*size = 0;
	for (int i = 0; i < getSize(service->repo); i++) {
		Offer* current = service->repo->array->elements[i];
			offers[(*size)++] = service->repo->array->elements[i];
	}
	return offers;

}

// Returns the offers which have the string contained in their destination

TElem* sameTypeOffers(Service* service, char* string, int* size) {
		TElem* offers = malloc(sizeof(TElem) * 100);
		Offer* aux = malloc(sizeof(Offer));
		if (strcmp(string, "null") == 0) {
			*size = getSize(service->repo);
			offers= service->repo->array->elements;
		}
		else
		{
			*size = 0;
			{for (int i = 0; i < getSize(service->repo); i++) {
				Offer* current = service->repo->array->elements[i];
				if (strstr(current->destination, string) != NULL) {
					offers[(*size)++] = service->repo->array->elements[i];
				}
			}}
		}
		for (int index = 0; index < *size; index++)
		{
			for (int index2 = index + 1; index2 < *size; index2++)
			{
				if (getPrice(offers[index]) > getPrice(offers[index2]))
				{
						aux = offers[index];
						offers[index] = offers[index2];
						offers[index2] = aux;
				}
			}
		}
		return offers;

	}

// verify which of the two dates is older.
// if currentOfferDate is older then it will return 1
// otherwise will return 0
int verifyTypeIsSmaller( char* stringGivenDate, char* currentOfferDate)
{
	int dayGiven, monthGiven, yearGiven, dayCurrent, monthCurrent, yearCurrent;
	sscanf(stringGivenDate, "%d/%d/%d", &dayGiven, &monthGiven, &yearGiven);
	sscanf(currentOfferDate, "%d/%d/%d", &dayCurrent, &monthCurrent, &yearCurrent);
	if (yearCurrent > yearGiven) {
		return 1;
	}
	else if (yearCurrent < yearGiven) {
		return 0;
	}
	else {
		if (monthCurrent > monthGiven) {
			return 1;
		}
		else if (monthCurrent < monthGiven) {
			return 0;
		}
		else {
			if (dayCurrent > dayGiven) {
				return 1;
			}
			else if (dayCurrent < dayGiven) {
				return 0;
			}
			else {
				return 0;
			}
		}
	}
}

// returning offers array with offers that are the same type as the one inputted by the user
// and with the Departure Date bigger than the one inputted by the user.
TElem* sameTypeButAfterDepartureDate(Service* service, char* stringType, char* stringGivenDate,int* size) {
	TElem* offers = malloc(sizeof(TElem) * 100);

	char* currentOfferDate[30];
	*size = 0;
	for (int i = 0; i < getSize(service->repo); i++) {
		Offer* current = service->repo->array->elements[i];
		strcpy(currentOfferDate, current->departureDate);
		if (strstr(current->type, stringType) != NULL && verifyTypeIsSmaller(stringGivenDate,currentOfferDate)==1) {
			offers[(*size)++] = service->repo->array->elements[i];
		}
	}

	return offers;

}
// Order in descending order by Date by comparing every date from year to day to see which one is older.
TElem* sameTypeButAfterDepartureDateDescendingOrderByDate(Service* service, char* stringType, char* stringGivenDate, int* size)
{
	TElem* offers = malloc(sizeof(TElem) * 100);
	Offer* aux = malloc(sizeof(Offer));
	char* currentOfferDate[30];
	*size = 0;
	for (int i = 0; i < getSize(service->repo); i++) {
		Offer* current = service->repo->array->elements[i];
		strcpy(currentOfferDate, current->departureDate);
		if (strstr(current->type, stringType) != NULL && verifyTypeIsSmaller(stringGivenDate, currentOfferDate) == 1) {
			offers[(*size)++] = service->repo->array->elements[i];
		}
	}
	for (int index = 0; index < *size; index++)
	{
		for (int index2 = index + 1; index2 < *size; index2++)
		{
			Offer* current = offers[index];
			Offer* current2 = offers[index2];
			// Extract the day,month,year from every string.
			int day1, month1, year1;
			sscanf(current->departureDate, "%d/%d/%d", &day1, &month1, &year1);
			int day2, month2, year2;
			sscanf(current2->departureDate, "%d/%d/%d", &day2, &month2, &year2);
			if (year1 < year2) {
				aux = offers[index];
				offers[index] = offers[index2];
				offers[index2] = aux;
			}
			else if (year1 == year2) {
				// If the year components are equal, compare the month components
				if (month1 < month2) {
					aux = offers[index];
					offers[index] = offers[index2];
					offers[index2] = aux;
				}
				else if (month1 == month2) {
					// If the month components are equal, compare the day components
					if (day1 < day2) {
						aux = offers[index];
						offers[index] = offers[index2];
						offers[index2] = aux;
					}
				}
			}
		}
	}
	return offers;
}
// Function to sort in Descending order all the offers.
TElem* sameTypeButAfterDepartureDateDescendingOrderByPrice(Service* service, char* stringType, char* stringGivenDate, int* size)
{
	TElem* offers = malloc(sizeof(TElem) * 100);
	Offer* aux = malloc(sizeof(Offer));
	char* currentOfferDate[30];
	*size = 0;
	for (int i = 0; i < getSize(service->repo); i++) {
		Offer* current = service->repo->array->elements[i];
		strcpy(currentOfferDate, current->departureDate);
		if (strstr(current->type, stringType) != NULL && verifyTypeIsSmaller(stringGivenDate, currentOfferDate) == 1) {
			offers[(*size)++] = service->repo->array->elements[i];
		}
	}
	// Sorting algorithm
	for (int index = 0; index < *size; index++)
	{
		for (int index2 = index + 1; index2 < *size; index2++)
		{	//verifying which price is bigger and swapping the elements;
			if (getPrice(offers[index]) < getPrice(offers[index2]))
			{
				aux = offers[index];
				offers[index] = offers[index2];
				offers[index2] = aux;
			}
		}
	}
	return offers;
}

Offer* findOfferByDestinationAndDepartureDateServiceReturningOffer(Service* service, char* stringDestination, char* stringDepartureDate) {
	return findOfferByDestinationAndDepartureDateReturningOffer(service->repo, stringDestination, stringDepartureDate);
}
 
int updateOfferService(Service* service, char* existingDestination, char* existingDepartureDate, char*type, char* destination, char* departureDate, int price)
{
	Offer* newOffer = createOffer(type, destination, departureDate, price);
	return updateOffer(service->repo, existingDestination, existingDepartureDate,newOffer);
}

int removeOfferService(Service* service, char* destination, char* departureDate) {
	Offer* existingOffer = getOffer(service->repo, destination, departureDate);
	return removeOffer(service->repo, existingOffer);
}

int addOfferService(Service* service, char* type, char* destination, char* departureDate,int price) {
	Offer* newOffer = createOffer(type, destination, departureDate,price);
	return addOffer(service->repo, newOffer);
}

//void interchange(Service* service, Repository* undo, int index) {
//}


int findOfferByDestinationAndDepartureDateService(Service* service, char* stringDestination, char* stringDepartureDate) {
	return findOfferByDestinationAndDepartureDate(service->repo, stringDestination, stringDepartureDate);
}

void addEntries(Service* service) {
	Offer* o1 = createOffer("mountain", "Brasov", "14/07/2018", 180);
	Offer* o2 = createOffer("seaside", "Constanta", "21/11/2020", 800);
	Offer* o3 = createOffer("citybreak", "Sydney", "12/10/2021", 500);
	Offer* o4 = createOffer("citybreak", "Maldives", "03/11/2011", 3);
	Offer* o5 = createOffer("mountain", "Paris", "08/07/1989", 1);
	Offer* o6 = createOffer("seaside", "Dubai", "26/12/2005", 34);
	Offer* o7 = createOffer("citybreak", "BoraBora", "23/02/2007", 43959);
	Offer* o8 = createOffer("citybreak", "Tokyo", "17/09/2021", 329);
	Offer* o9 = createOffer("mountain", "Rome", "11/04/2018", 182);
	Offer* o10 = createOffer("seaside", "Jaipur", "26/03/2020", 8003);
	addOffer(service->repo, o1);
	addOffer(service->repo, o2);
	addOffer(service->repo, o3);
	addOffer(service->repo, o4);
	addOffer(service->repo, o5);
	addOffer(service->repo, o6);
	addOffer(service->repo, o7);
	addOffer(service->repo, o8);
	addOffer(service->repo, o9);
	addOffer(service->repo, o10);

}

void testService() {
	Repository* repos = createRepo();
	Service* servi = createService(repos);
	int dayTest;
	int monthTest;
	int yearTest;
	int verifyDepartureDate(Service * service, char* departureDate, int* day, int* month, int* year);
	char departureDateTest[30];
	strcpy(departureDateTest, "10/12/2002");
	assert(verifyDepartureDate(servi, departureDateTest, &dayTest, &monthTest, &yearTest)==1);
	Offer* o1 = createOffer("mountain", "brasov", "14/07/2018", 180);
	Offer* o2 = createOffer("seaside", "constanta", "26/11/2020", 800);
	Offer* o3 = createOffer("citybreak", "china", "17/02/2021", 500);
	Offer* o4 = createOffer("citybreak", "china", "17/02/2021", 100);
	addOffer(servi->repo, o1);
	addOffer(servi->repo, o2);
	addOffer(servi->repo, o3);
	addOffer(servi->repo, o4);
	char typeTest[30];
	char departureDateTest2[30];
	strcpy(departureDateTest, "20/12/2002");
	strcpy(typeTest, "mountain");
	assert(verifyTypeIsSmaller(departureDateTest, departureDateTest2) == 0);

}