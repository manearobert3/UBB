#include "Engine.h"

double ElectricEngine::getPrice()
{
	return basePrice + autonomy*(0.01);
}

string ElectricEngine::toString()
{
	string string;
	string = "Body style of car is : " + bodyType + "\n" + "type of engine is: Electric\n" + "Autonomy is: " + to_string(autonomy) + "\n";
	return string;
}

double TurboEngine::getPrice()
{
	return basePrice+100;
}

string TurboEngine::toString()
{
	string string;
	string = "Body style of car is : " + bodyType + "\n" + "type of engine is: Turbo\n";
	return string;
}
