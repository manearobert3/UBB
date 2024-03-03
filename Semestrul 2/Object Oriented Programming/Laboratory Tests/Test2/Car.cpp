#include "Car.h"

double Car::computePrice()
{
	if (bodyStyle == "Sedan")
		return 8000 + engine->getPrice();
	else
		return 9000 + engine->getPrice();
}

string Car::toString() {
	string s;
	s = /*bodyStyle + " Price: " + std::to_string(computePrice()) +*/ engine->toString();
	return s;
}