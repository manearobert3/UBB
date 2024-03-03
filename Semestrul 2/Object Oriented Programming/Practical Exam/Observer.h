#pragma once
#include<vector>
class Observer {
public:
	virtual void update() = 0;

};

class Observable {
	std::vector<Observer*> entities;
protected:
	void notify() {
		for (auto observ:entities) {
			observ->update();
		}
	}
public:
	void addObserver(Observer* obsv) {
		entities.push_back(obsv);
	}
	void removeObserver(Observer* obsv) {
		entities.erase(std::remove(entities.begin(), entities.end(), obsv));
	}
};