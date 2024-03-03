#pragma once
#include "repository.h"
class Service {
private:
	Repository repo;

public:
	vector<Application> returnAll() {
		return this->repo.returnAll();
	}
	vector<Application> sortByName();
	static bool compareName(Application a1, Application a2);
};