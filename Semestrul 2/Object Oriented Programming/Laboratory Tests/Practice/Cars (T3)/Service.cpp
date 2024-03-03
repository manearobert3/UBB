#include "Service.h"

void Service::addCarService(Car& car)
{
	this->repo.addCarRepo(car);
}

void Service::deleteCarService(Car& car)
{
	int index = repo.findCarPosition(car);
	if (index == -1) return;
	this->repo.deleteCarRepo(index);
}

void Service::updateCarService(int index, Car& car){
	this->repo.updateCarRepo(index, car);
}

