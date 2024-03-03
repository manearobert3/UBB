#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include"OperationDynamicArray.h"

Ui* createUi(Service* service) {
	Ui* newUi = malloc(sizeof(Ui));
	if (newUi == NULL)
		return NULL;
	newUi->service = service;
	return newUi;
}

void destroyUi(Ui* ui) {
	destroyService(ui->service);
	free(ui);
}

void printMenu() {
	printf("Commands:\n");
	printf("\t1. Add offer\n");
	printf("\t2. Delete offer\n");
	printf("\t3. Update offer\n");
	printf("\t4. Display tourism offers by given string\n");
	printf("\t5. Display tourism offers by given type and after a given date\n");
	//printf("\t6. Display tourism offers bigger than a given price\n");
	printf("\t0. Exit\n");
}

void startMenu(Ui* ui) {
	//addEntries(ui->service);
	//char type[20];
	//char destination[20];
	//char departureDate[20];
	//int price;
	//int index = 0;
	//printf("Give type,destination,departure date and price\n");
	//scanf("%s %s %s %d", &type, &destination, &departureDate, &price);
	OperationDynamicArray* operationArray = malloc(sizeof(OperationDynamicArray)*10);
	operationArray = createOperationDynamicArray(20,destroyOperationDynamicArray);
	//Offer* offer = createOffer(type, destination, departureDate, price);
	Repository* undo = createRepo();
	//printf("Give type,destination,departure date and price\n");
	//scanf("%s %s %s %d", &type, &destination, &departureDate, &price);
	//Offer* offer1 = createOffer(type, destination, departureDate, price);
	//addToOperationArrayUpdate(operationArray, offer1,offer, 3);
	int contorArrayOperations = 0;
	int* operationsType;
	operationsType=malloc(sizeof(int) * 10);
	while (1) {
		printMenu();
		int day;
		int month;
		int year;
		int option;
		scanf("%d", &option);
		if (option == 0) {
			break;
		}
		if (option == 1)
		{
			char type[20];
			char destination[20];
			char departureDate[20];
			int price;
			int index = 0;
			printf("Give type,destination,departure date and price\n");
			scanf("%s %s %s %d", &type, &destination, &departureDate, &price);
			if (verifyDepartureDate(ui->service, departureDate, &day, &month, &year) == 0) {
				printf("Not a valid departure date type, format must be DD/MM/YYYY\n");
			}
			else {
				if (verifyType(ui->service, type) != 0) {

					int verifyInputValid = addOfferService(ui->service, type, destination, departureDate, price);
					if (verifyInputValid == 1) {
						printf("Valid Offer\n");
						TElem* offer = createOffer(type, destination, departureDate, price);
						//printf("%s\n", toString(offer));
						addOfferUndo(undo,offer);
						operationsType[contorArrayOperations] = 1;
						contorArrayOperations = contorArrayOperations+1;
					}
					else {
						printf("Not a valid offer\n");
					}
				}
				else
					printf("Not a valid type of offer\n");
			}
		}
		else if (option == 7) {
			//popOperation(operationArray);
			//if (returnLastOperationType(operationArray)/*->operationType[operationArray->length]*/ == 1)
			//{
			//	removeOfferService(ui->service, getDestination(returnLastOperation(operationArray)), getDepartureDate(returnLastOperation(operationArray)));
			//}
			//else if (returnLastOperationType(operationArray)/*->operationType[operationArray->length]*/ == 2)
			//	//char* type, char* destination, char* departureDate,int price
			//{
			//	addOfferService(ui->service, getType(returnLastOperation(operationArray)), getDestination(returnLastOperation(operationArray)), getDepartureDate(returnLastOperation(operationArray)), getPrice(returnLastOperation(operationArray)));
			//}
			//else if (returnLastOperationType(operationArray)/*->operationType[operationArray->length]*/ == 3)
			//	//char* type, char* destination, char* departureDate,int price
			//{
			//	removeOfferService(ui->service, getDestination(returnLastOperation(operationArray)), getDepartureDate(returnLastOperation(operationArray)));
			//	popOperation(operationArray);
			//	addOfferService(ui->service, getType(returnLastOperation(operationArray)), getDestination(returnLastOperation(operationArray)), getDepartureDate(returnLastOperation(operationArray)), getPrice(returnLastOperation(operationArray)));

			//	printf("%s\n", toString(returnLastOperation(operationArray)));
			//}
			if (operationsType[contorArrayOperations - 1] == 1 && contorArrayOperations >= 0) {
				interchangeRemove(ui->service->repo, undo, contorArrayOperations);
				contorArrayOperations = contorArrayOperations - 1;
			}
			if (operationsType[contorArrayOperations - 1] == 2 && contorArrayOperations >= 0) {
				interchangeAdd(ui->service->repo, undo, contorArrayOperations);
				contorArrayOperations = contorArrayOperations - 1;
			}
			if (operationsType[contorArrayOperations-1] == 3 && contorArrayOperations >= 0) {
				interchangeRemove(ui->service->repo, undo, contorArrayOperations-1);
				interchangeAdd(ui->service->repo, undo, contorArrayOperations);
				contorArrayOperations = contorArrayOperations - 1;
				contorArrayOperations = contorArrayOperations - 1;
			}
		}
		else if (option == 8) {
			if (operationsType[contorArrayOperations] == 1 && contorArrayOperations >= 0) {
				interchangeAdd(ui->service->repo, undo, contorArrayOperations+1);
				contorArrayOperations = contorArrayOperations + 1;
			}
			if (operationsType[contorArrayOperations] == 2 && contorArrayOperations >= 0) {
				interchangeRemove(ui->service->repo, undo, contorArrayOperations+1);
				contorArrayOperations = contorArrayOperations + 1;
			}
			if (operationsType[contorArrayOperations] == 3 && contorArrayOperations >= 0) {
				interchangeRemove(ui->service->repo, undo, contorArrayOperations);
				contorArrayOperations = contorArrayOperations + 1;
				interchangeAdd(ui->service->repo, undo, contorArrayOperations);
				contorArrayOperations = contorArrayOperations + 1;
			}

		}
		else if (option == 2)
		{
			char stringDestination[20];
			char stringDepartureDate[20];
			printf("Give destination and departure date to remove an offer ");
			scanf("%s %s", &stringDestination, &stringDepartureDate);
			if (verifyDepartureDate(ui->service, stringDepartureDate, &day, &month, &year) == 0) {
				printf("Not a valid departure date type, format must be DD/MM/YYYY\n");
			}
			else
			{
				if (findOfferByDestinationAndDepartureDateService(ui->service, stringDestination, stringDepartureDate) == 1) {
					Offer* current=findOfferByDestinationAndDepartureDateServiceReturningOffer(ui->service, stringDestination, stringDepartureDate);
					int verifyInputValid = removeOfferService(ui->service, stringDestination, stringDepartureDate);
					if (verifyInputValid == 1) {
						printf("Removed the offer\n");
						operationsType[contorArrayOperations] = 2;
						addOfferUndo(undo, current);
						contorArrayOperations = contorArrayOperations + 1;
						/*addToOperationArray(operationArray, offer, 2);*/
					}
					else {
						printf("Couldn't remove the offer\n");
					}
				}
				else
					printf("There is no such offer");
			}
		}
		else if (option == 3)
		{
			char existingDestination[20];
			char existingDepartureDate[20];
			printf("Give destination and departure date for the offer to be updated\n");
			scanf("%s %s", &existingDestination, &existingDepartureDate);
			printf("\n");
			if (verifyDepartureDate(ui->service, existingDepartureDate, &day, &month, &year) == 0) {
				printf("Not a valid departure date type, format must be DD/MM/YYYY\n");
			}
			else {
				char type[20];
				char destination[20];
				char departureDate[20];
				int price;
				printf("Give type,destination,departure date and price for updating an offer\n");
				scanf("%s %s %s %d", &type, &destination, &departureDate, &price);
				TElem* offerInitial = createOffer(type, destination, departureDate, price);
				TElem* offerAfterUpdate = findOfferByDestinationAndDepartureDateServiceReturningOffer(ui->service, existingDestination, existingDepartureDate);
				int verifyInput = updateOfferService(ui->service, existingDestination, existingDepartureDate, type, destination, departureDate, price);
				if (verifyInput == 1) {
					printf("Updated offer\n");
					addOfferUndo(undo, offerInitial);
					operationsType[contorArrayOperations] = 3;
					contorArrayOperations = contorArrayOperations + 1;
					addOfferUndo(undo, offerAfterUpdate);
					operationsType[contorArrayOperations] = 3;
					contorArrayOperations = contorArrayOperations + 1;
				}
				else {
					printf("Couldn't update offer\n");
				}
			}
		}
		else if (option == 4)
		{
			char string[20];
			int size;
			printf("Give string to contained in the destination or 'null' if you want to list all offers: ");
			scanf("%s", &string);
			TElem* offers = malloc(sizeof(TElem));
			offers = sameTypeOffers(ui->service, string, &size);
			for (int i = 0; i < size; i++) {
				printf("%s\n", toString(offers[i]));
			}
		}
		else if (option == 5)
		{
			char string[20];
			char inputtedDate[20];
			int size;
			printf("Give type of offer (between mountain,seaside,citybreak) and a date");
			scanf("%s", &string);
			scanf("%s", &inputtedDate);
			int option2;
			printf("Choose a sorting:\n");
			printf("1. Descending by price");
			printf("2. Descending by date");
			printf("3. No sorting");
			scanf("%d", &option2);

			if (option2 == 3) {
				TElem* offers = malloc(sizeof(TElem));
				TElem* (*sameTypeButAfterDepartureDatPointer)(Service*, char*, char*,int*) = &sameTypeButAfterDepartureDate;
				offers = (*sameTypeButAfterDepartureDatPointer)(ui->service, string, inputtedDate,&size);
				//offers = sameTypeButAfterDepartureDate(ui->service, string, inputtedDate, &size);
				for (int i = 0; i < size; i++) {
					printf("%s\n", toString(offers[i]));
				}
				free(offers);
			}
			else if (option2 == 2) {
				TElem* offers = malloc(sizeof(TElem));
				//offers = sameTypeButAfterDepartureDateDescendingOrderByDate(ui->service, string, inputtedDate, &size);
				TElem* (*sameTypeButAfterDepartureDateDescendingOrderByDatePointer)(Service*, char*, char*, int*) = &sameTypeButAfterDepartureDateDescendingOrderByDate;
				offers = (*sameTypeButAfterDepartureDateDescendingOrderByDatePointer)(ui->service, string, inputtedDate, &size);
				for (int i = 0; i < size; i++) {
					printf("%s\n", toString(offers[i]));

				}
				free(offers);
			}
			else if (option2 == 1) {
				TElem* offers = malloc(sizeof(TElem));
				//offers = sameTypeButAfterDepartureDateDescendingOrderByPrice(ui->service, string, inputtedDate, &size);
				TElem* (*sameTypeButAfterDepartureDateDescendingOrderByPricePointer)(Service*, char*, char*, int*) = &sameTypeButAfterDepartureDateDescendingOrderByPrice;
				offers = (*sameTypeButAfterDepartureDateDescendingOrderByPricePointer)(ui->service, string, inputtedDate, &size);
				for (int i = 0; i < size; i++) {
					printf("%s\n", toString(offers[i]));
				}
				free(offers);
			}
			else printf("Not a valid option\n");
			}
			else if (option == 6)
			{
				int price1;
				int size;
				printf("Give price ");
				scanf("%d", &price1);
				TElem* offers = malloc(sizeof(TElem));
				TElem* (*sameTypeOffersBiggerThanPricePointer)(Service*, int*, int) = &sameTypeOffersBiggerThanPrice;
				offers = (*sameTypeOffersBiggerThanPricePointer)(ui->service, &size, price1);
				for (int i = 0; i < size; i++) {
					printf("%s\n", toString(offers[i]));
				}
				free(offers);
			}
			/*else if (option == 7)
			{

			char string[20];
			int size;
			destroyRepository(ui->service->repo);
			ui->service->repo = createRepo();
			ui->service->repo = makeCopyOfRepo(repositoryForUndo[repositoryForUndoLength-1]);
			repositoryForUndoLength = repositoryForUndoLength - 1;
			TElem* offers = malloc(sizeof(TElem));
			offers = sameTypeOffersForUndo(ui->service, string, &size);
			for (int i = 0; i < size; i++) {
				printf("%s\n", toString(offers[i]));
			}*/
			//UndoOperationService(ui->service);
			//}
			else
			{
				printf("Not a valid option");
			}
	}

}