#include"service.h"
#include<vector>
#include<algorithm>

Service::Service() {
	this->repo = Repo();
}
Service::~Service() {};
// adds protein after virifies for existence of the protein in the entire protein vector;
bool Service::addProtein(Protein protein) {
	if (this->repo.verifyExistence(protein) == false) {
		this->repo.addProtein(protein);
		return true;
	}
	else return false;

}

bool Service::removeProtein(Protein protein) {
	if (this->repo.verifyExistence(protein) == true) {
		this->repo.removeProtein(protein);
		return true;
	}
	else return false;

}
std::vector<Protein> Service::getProtein() const {
	return this->repo.getProteins();
}