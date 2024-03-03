#include"service.h"
#include<string>
#include<algorithm>
using namespace std;
vector<Application> Service::sortByName()
{
	vector<Application> apps = this->repo.returnAll();
	sort(apps.begin(), apps.end(), compareName);
	return apps;
}

bool Service::compareName(Application a1, Application a2)
{
	return a1.getName() < a2.getName();
}
