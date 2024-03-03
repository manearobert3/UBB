#include "service.h"
#include<algorithm>
#include<string>
#include<vector>
vector<Application> Service::sortByName()
{
	vector<Application> sorted;
	sorted = this->repo.returnAll();
	std::sort(sorted.begin(), sorted.end(), nameSort);
	return sorted;
}

bool Service::nameSort(Application s1, Application s2)
{
	return s1.getName() < s2.getName();
}
