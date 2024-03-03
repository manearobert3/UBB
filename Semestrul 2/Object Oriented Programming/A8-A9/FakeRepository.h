#pragma once
#include "repository.h"

class FakeRepository : public Repository {

public:
	bool checkPresenceOfEntity;
	bool checkAuthenticity(Movie inputtedMovie);

};