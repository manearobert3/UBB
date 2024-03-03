#pragma once
#include<vector>
#include<string>
#include "domain.h"
class Repository {
private:
	vector<Application> apps;
public:
	Repository() { readFromFile(); };
	~Repository() {};
	void readFromFile();
	vector<Application> returnAll(); 
};