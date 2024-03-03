#pragma once
#include "Repository.h"
#include "Domain.h"

class Service
{
public:
	Service(const Repository& repository) : repo{ repository } {};
	//~Service() {};
	Repository getRepo() const { return this->repo; }
	void addCarService(Car& car);
	void deleteCarService(Car& car);
	void updateCarService(int index, Car& car);
private:
	Repository repo;
};
