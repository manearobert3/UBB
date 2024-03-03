#pragma once
#include"Engine.h"
#include"Car.h"
#include<vector>
using namespace std;


class Service {
private:
	Engine* engine;
	vector<Car> cars;
public:
	void addCar(string bodyStyle, string engineType, int autonomy);
	vector<Car> getCarsWithMaxPrice(double maxPrice);
	void writeToFile(string filename, vector<Car> cars);
	vector<Car> getAllCars();


};