#include "Repository.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

vector<Car> Repository::getOldCarsList()
{
	vector<Car>old_cars;

	for (Car& car : car_list) {
		if (car.getYear() < 2013) {
			old_cars.push_back(car);
		}
	}
	return old_cars;
}

void Repository::addCarRepo(Car& car)
{
	this->car_list.push_back(car);
}

void Repository::deleteCarRepo(int index)
{
	this->car_list.erase(this->car_list.begin() + index);
}

void Repository::updateCarRepo(int index, Car& car){
	this->car_list[index] = car;
}

int Repository::findCarPosition(Car& car_to_be_found)
{
	vector<Car>::iterator it;
	it = find_if(car_list.begin(), car_list.end(), [&](Car& car) {return areCarsTheSame(car, car_to_be_found); });
	if (it != car_list.end()) {
		return it - car_list.begin();
	}
	return -1;
}

void Repository::readCarsFromFile(string filename)
{
	fstream file;
	string token, line;
	vector<string> string_vector;
	file.open(this->filename, std::ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			stringstream ss(line);
			while (getline(ss, token, ',')) {
				string_vector.push_back(token);
			}
			if (string_vector.size() == 4) {
				Car car(string_vector[0], stoi(string_vector[1]), string_vector[2], string_vector[3]);
				this->car_list.push_back(car);
			}
			string_vector.clear();
		}
		file.close();
	}
	else {
		cout << "file is fucked";
	}
}
