#pragma once
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Engine {
protected:
	string bodyType;
	double basePrice;

public:
	Engine(string body) :bodyType{ body }, basePrice { 3000 } {};
	virtual double getPrice() { return basePrice; };
	virtual string toString()=0;

};

class ElectricEngine : public Engine {
private:
	int autonomy;

public:
	ElectricEngine(string body, int autonomy) :Engine(body), autonomy{ autonomy } {};
	double getPrice();
	string toString();
};

class TurboEngine : public Engine {
private:

public:
	TurboEngine(string body) :Engine(body) {};
	double getPrice();
	string toString();
};