#pragma once
#include<vector>
#include<string>
class Volunteer {
private:
	std::string name, email, listOfInterests, department;
public:
	Volunteer(std::string name, std::string email, std::string listOfInterests, std::string department) :name{ name }, email{ email },listOfInterests { listOfInterests }, department{ department } {};
	~Volunteer() {};
	std::string getName() {
		return name;
	}
	std::string getEmail()
	{
		return email;
	}
	std::string getListOfInterests()
	{
		return listOfInterests;
	}
	std::string getDepartment()
	{
		return department;
	}
	void setDepartment(std::string newDepartment) {
		department = newDepartment;
	}
};