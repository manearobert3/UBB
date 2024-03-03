#pragma once
#include"Repository.h"
class Service : public Observable {
private:
	Repository& repo;

public:
	Service(Repository& repo) : repo{ repo } {};
	~Service() {};
	std::vector<Department>& getDepartments() {

		return this->repo.getDepartments();
	}
	std::vector<Volunteer>& getVolunteers() {
		return this->repo.getVolunteers();
	}
	void addVolunteer(std::string name, std::string email, std::string listOfInterests) {
		this->repo.addVolunteer( name,email, listOfInterests);
		this->notify();
	}
	void notifyObs() {
		this->notify();
	}
	void sortRepo() {
		this->repo.sortRepo();
		this->notify();
	}
};