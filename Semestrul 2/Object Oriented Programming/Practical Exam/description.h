#pragma once
#include<iostream>
#include<string>
class Department {

private:
	std::string name, description;
public:
	Department(std::string name, std::string description) :name{ name }, description{ description } {};
	~Department() {};
	std::string getName() {
		return name;
	}
	std::string getDescription()
	{
		return description;
	}
};