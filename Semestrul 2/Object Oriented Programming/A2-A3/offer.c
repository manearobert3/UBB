
#include "offer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


Offer* createOffer(char* type, char* destination, char* departureDate, int price)

{
	Offer* newOffer = malloc(sizeof(Offer)*10);
	if (newOffer == NULL)
		return newOffer;
	newOffer->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (newOffer->type == NULL)
	{
		free(newOffer);
		return NULL;
	}
	strcpy(newOffer->type, type);
	newOffer->destination = malloc(sizeof(char) * (strlen(destination) + 1));
	if (newOffer->destination == NULL)
	{
		free(newOffer->type);
		free(newOffer);
		return NULL;
	}
	strcpy(newOffer->destination, destination);
	newOffer->departureDate = malloc(sizeof(char) * (strlen(departureDate) + 1));
	if (newOffer->departureDate == NULL)
	{
		free(newOffer->type);
		free(newOffer->destination);
		free(newOffer);
		return NULL;
	}
	strcpy(newOffer->departureDate, departureDate);
	newOffer->price = price;
	return newOffer;
}

void destroyOffer(Offer* offer)
{
	if (offer == NULL)
		return;
	free(offer->type);
	free(offer->destination);
	free(offer->departureDate);
	free(offer);
}


char* getType(Offer* offer) {
	return offer->type;
}

char* getDepartureDate(Offer* offer) {
	return offer->departureDate;
}

char* getDestination(Offer* offer) {
	return offer->destination;
}

int getPrice(Offer* offer) {
	return offer->price;
}

char* toString(Offer* offer) {
	char* str[30];
	sprintf(str, "%s %s %s %d", offer->type, offer->departureDate, offer->destination, offer->price);
	return str;
}

void testOffer() {
	Offer* o1 = createOffer("mountain", "brasov", "14/07/2018", 180);
	Offer* o2 = createOffer("seaside", "constanta", "26/11/2020", 800);
	Offer* o3 = createOffer("citybreak", "china", "17/02/2021", 500);
	char type[20];
	char destination[20];
	char date[20];
	int price;
	strcpy(type, "mountain");
	assert(strcmp(getType(o1),type)==0);
	strcpy(destination, "brasov");
	assert(strcmp(getDestination(o1),destination)==0);
	strcpy(date, "14/07/2018");
	assert(strcmp(getDepartureDate(o1), date)==0);
	price = 180;
	assert(getPrice(o1)==180);

	
}
