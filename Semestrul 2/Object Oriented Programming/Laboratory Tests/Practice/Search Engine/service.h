#pragma once
#include "repository.h"
#include<string>
class Service {
private:
	Repository repo;

public:
	vector<Application> returnAll() {
		return this->repo.returnAll();
	}
	vector<Application> sortByName();
	static bool nameSort(Application s1, Application s2);
};