#pragma once
#include <vector>
#include <string>
#include "Domain.h"

class Repository
{
public:
	Repository(const string& filename) :filename{ filename } { readCarsFromFile(this->filename);};
	~Repository() {};
	vector<Car> getCarList() { return this->car_list; }
	vector<Car> getOldCarsList();

	void addCarRepo(Car& car);
	void deleteCarRepo(int index);
	void updateCarRepo(int index, Car& car);
	int findCarPosition(Car& car);
	bool areCarsTheSame(Car& c1, Car& c2) { return c1.getYear() == c2.getYear() && c1.getColor() == c2.getColor() && c1.getName() == c2.getName(); }
	void readCarsFromFile(string filename);
private:
	vector<Car> car_list;
	string filename;
};

