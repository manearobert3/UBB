#pragma once
#include "vegetable.h"
#include<vector>
#include<string>
using namespace std;


class Repository
{
private:
	vector<Vegetable> vegetables;
public:
	Repository() { readFromFile(); };
	~Repository() {};
	void addVeg(Vegetable veg);
	void readFromFile();
	vector<Vegetable> returnAll();
	vector<Vegetable> sortFamily();
	vector<Vegetable> getVeg(string vegetable);
	string getFamilyFromVeg(string vegetable);
	string getEatable(string vegetable);
	int getVegFromFamily(string family);
	static bool compareFamily(Vegetable s1, Vegetable s2);
	static bool equalFamily(Vegetable s1, Vegetable s2);
};
