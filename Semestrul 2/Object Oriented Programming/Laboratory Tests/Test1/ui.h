#pragma once
#include"service.h"
class UI
{
private:
	Service service;
public:
	UI();
	~UI();
	void printMenu();
	void printAdd();
	void printRemove();
	void printProtein();
	void run();
};