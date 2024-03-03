#pragma once
#include"Service.h"
#include<iostream> 
using namespace std;
class UI {
private:
	Service service;
public:
	void start();
	void add();
	void print();

};