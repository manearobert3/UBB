#include "repository.h"
#include<fstream>
#include <algorithm>
#include <string>
#include<sstream>
void Repository::addVeg(Vegetable veg)
{
	this->vegetables.push_back(veg);
}

void Repository::readFromFile()
{

	std::ifstream fin("veg.txt");
	if (!fin.is_open())
		throw exception();
	Vegetable veg;
	string string;
	while (std::getline(fin, string))
	{
		std::string family, name, line;
		std::istringstream iss(string);
		iss >> family >> name >> line;
		veg.setFamily(family);
		veg.setName(name);
		veg.setList(line);
		this->vegetables.push_back(veg);
	}
	fin.close();
}

vector<Vegetable> Repository::returnAll()
{
	return this->vegetables;
}

vector<Vegetable> Repository::sortFamily()
{
	vector<Vegetable> unique;
	std::sort(vegetables.begin(),vegetables.end(), compareFamily);
	for (int i = 0; i < vegetables.size(); i++)
	{
		unique.push_back(vegetables[i]);
	}
	std::sort(unique.begin(), unique.end(),compareFamily);
	auto it=std::unique(unique.begin(), unique.end(), equalFamily);
	unique.resize(std::distance(unique.begin(), it));
		return unique;
}

vector<Vegetable> Repository::getVeg(string vegetable)
{
	vector<Vegetable> unique;
	for (int i = 0; i < vegetables.size(); i++)
	{	if(vegetables[i].getFamily()==vegetable)
			unique.push_back(vegetables[i]);
	}
	return unique;
}

string Repository::getFamilyFromVeg(string vegetable)
{
	for (int i = 0; i < vegetables.size(); i++)
	{
		if (vegetables[i].getName() == vegetable)
			return vegetables[i].getFamily();
	}
	return "";
}

string Repository::getEatable(string vegetable)
{
	for (int i = 0; i < vegetables.size(); i++)
	{
		if (vegetables[i].getName() == vegetable)
			return vegetables[i].getList();
	}
	return "";
}

int Repository::getVegFromFamily(string family)
{
	int contor = 0;
	for (int i = 0; i < vegetables.size(); i++)
	{
		if (vegetables[i].getFamily() == family)
			contor++;
	}
	return contor;
}

bool Repository::compareFamily(Vegetable s1, Vegetable s2)
{
	return s1.getFamily() < s2.getFamily();
}

bool Repository::equalFamily(Vegetable s1, Vegetable s2)
{
	return s1.getFamily() == s2.getFamily();
}
