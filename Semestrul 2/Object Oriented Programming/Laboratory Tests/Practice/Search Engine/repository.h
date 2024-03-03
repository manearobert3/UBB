#pragma once
#include<string>
#include<vector>
#include"domain.h"
using namespace std;
class Repository {
private:
	vector<Application> apps;
public:
	Repository() { readFromFile(); };
	~Repository() {};
	void readFromFile();
	vector<Application> returnAll();
};