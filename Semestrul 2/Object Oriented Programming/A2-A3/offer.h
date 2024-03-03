#pragma once
typedef struct {
	char* type;
	char* destination;
	char* departureDate;
	int price;
}Offer;


Offer* createOffer(char* type, char* destination, char* departureDate, int price);

void destroyOffer(Offer* offer);

char* getDestination(Offer*);

char* getType(Offer*);

char* getDepartureDate(Offer*);

int getPrice(Offer*);

char* toString(Offer*);

void testOffer();
