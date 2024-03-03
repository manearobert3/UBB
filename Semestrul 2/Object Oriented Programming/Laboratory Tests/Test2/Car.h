#pragma once
#include<string>
#include"Engine.h"
using namespace std;

class Car {
private:
	string bodyStyle;
	Engine *engine;
public:
	Car(string body, Engine* engine) : bodyStyle{ body }, engine{ engine } {};
	double computePrice();
	string toString();
};