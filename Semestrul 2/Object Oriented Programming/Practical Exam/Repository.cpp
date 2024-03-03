#include "Repository.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include<string>
void Repository::readFromFile()
{
	std::ifstream file("departments.txt");
	std::string name, description, line;
	const char del = ',';
	while (getline(file, line)) {
		std::stringstream ss(line);
		getline(ss, name, del);
		getline(ss, description, del);
		this->departments.emplace_back(name, description);
	}
	file.close();
	file = std::ifstream("volunteers.txt");
	std::string email, listOfInterests, department;
	while (getline(file, line)) {
		std::stringstream ss(line);
		getline(ss, name, del);
		getline(ss, email, del);
		getline(ss, listOfInterests, del);
		getline(ss, department, del);
		if (department.empty()) {
			department = "";
		}
		this->volunteers.emplace_back(name, email, listOfInterests, department);
	}
	sort(volunteers.begin(), volunteers.end(), compareName);
	file.close();


}

void Repository::writeToFile()
{
	std::ofstream file("volunteers.txt");
	if (file.is_open()) {
		for (auto volunteer : volunteers)
			file << volunteer.getName() << "," << volunteer.getEmail() << "," << volunteer.getListOfInterests() << "," << volunteer.getDepartment()<<"\n";
	}
	file.close();
	file = std::ofstream("departments.txt");
	if (file.is_open()) {
		for (auto department : departments)
			file << department.getName() << "," << department.getDescription()<<"\n";
	}
	file.close();
}

void Repository::sortRepo()
{
	sort(volunteers.begin(), volunteers.end(), compareName);

}

void Repository::addVolunteer(std::string name, std::string email, std::string listOfInterests)
{
	this->volunteers.emplace_back(name, email, listOfInterests, "");
}


