#pragma once
#include"protein.h"
#include<vector>
class Repo
{
private:
	std::vector<Protein> proteins;
public:
	Repo();
	~Repo();
	std::vector<Protein> getProteins() const;
	void addProtein(Protein& protein);
	void removeProtein(Protein& protein);
	bool verifyExistence(Protein& proteinToVerify);
};