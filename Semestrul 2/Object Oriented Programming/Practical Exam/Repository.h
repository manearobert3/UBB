#pragma once
#include"Observer.h"
#include<vector>
#include"description.h"
#include"volunteer.h"
class Repository : public Observable {
	std::vector<Department> departments;
	std::vector<Volunteer> volunteers;

public:
	Repository() {
		this->readFromFile();
	}
	~Repository() { this->writeToFile(); 
	}
	void readFromFile();
	void writeToFile();
	std::vector<Department>& getDepartments() {

		return departments;
	}
	std::vector<Volunteer>& getVolunteers() {
		return volunteers;
	}
	static bool compareName(Volunteer volunteerNumber1, Volunteer volunteerNumber2) {
		return volunteerNumber1.getName() < volunteerNumber2.getName();
	}
	void sortRepo();
	void addVolunteer(std::string name, std::string email, std::string listOfInterests);
};