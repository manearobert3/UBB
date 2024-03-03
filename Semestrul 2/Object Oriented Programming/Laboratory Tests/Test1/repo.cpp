#include"repo.h"
#include<vector>
#include<iostream>

Repo::Repo()
{
	this->proteins = std::vector<Protein>();

}
Repo::~Repo()
{
}
void Repo::addProtein(Protein& proteinToBeAdded) {
	this->proteins.push_back(proteinToBeAdded);
}
void Repo::removeProtein(Protein& proteinToBeRemoved) {
	std::vector<Protein>::iterator iterator;
	iterator = std::find(this->proteins.begin(), this->proteins.end(), proteinToBeRemoved);
	this->proteins.erase(iterator);
}
bool Repo::verifyExistence(Protein& proteinToVerify) {
	std::vector<Protein>::iterator iterator;
	iterator = std::find(this->proteins.begin(), this->proteins.end(), proteinToVerify);
	if (iterator != proteins.end())
		return true;
	else return false;
}
std::vector<Protein> Repo::getProteins() const
{
	return this->proteins;
}