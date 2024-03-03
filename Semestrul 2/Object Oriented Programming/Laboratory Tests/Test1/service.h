#pragma once
#include"repo.h"
#include<vector>

class Service {
private:
	Repo repo;
public:
	Service();
	~Service();
	bool addProtein(Protein protein);
	bool removeProtein(Protein protein);
	std::vector<Protein> getProtein() const;
};