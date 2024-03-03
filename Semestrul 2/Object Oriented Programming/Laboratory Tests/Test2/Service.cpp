#include "Service.h"
#include"Car.h"
#include<vector>
#include<fstream>
void Service::addCar(string bodyStyle, string engineType, int autonomy)
{
	Engine* p1;
	if (engineType == "Electric")
		p1 = new ElectricEngine(bodyStyle, autonomy);
	else
		p1 = new TurboEngine(bodyStyle);
	Car newCar = Car(bodyStyle, p1);
	cars.push_back(newCar);
}

vector<Car> Service::getAllCars() {
	return cars;
}

vector<Car> Service::getCarsWithMaxPrice(double maxPrice)
{	
	vector<Car> maxPriceCars;
	for (auto car:cars) {
		if (car.computePrice() <= maxPrice)
			maxPriceCars.push_back(car);
	}
	return maxPriceCars;
}

void Service::writeToFile(string filename, vector<Car> cars)
{
	ofstream fout(filename);
	for (auto car : cars) {
		fout << car.toString();
	}
	fout.close();
}
