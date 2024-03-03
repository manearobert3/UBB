#pragma once
#include <string>
using namespace std;
class Car
{
public:
	Car(const string &name, int year, const string& model, const string& color) : name{ name }, year{ year }, model{ model }, color{ color } {};
	Car() : name{ "" }, year{ 0 }, model{ "" }, color{ "" } {};
	~Car() {};
	string getColor() const { return this->color; }
	string getName() const { return this->name; }
	string getModel() const { return this->model; }
	int getYear() const { return this->year; }
	string toString();

private:
	string name, model, color;
	int year;
};

