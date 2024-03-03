#pragma once
#include<string>
using namespace std;
class Vegetable {
private:
	string family, name, list;

public:
	Vegetable(string& family, string& name, string& list) : family{ family }, name{ name }, list{ list } {};
	Vegetable() : family{ "" }, name{ "" }, list{ "" } {};
	~Vegetable() {};
	string toString();
	void setFamily(string family) {
		this->family = family;
	}
	void setName(string name) {
		this->name = name;
	}
	void setList(string list) {
		this->list = list;
	}
	string getFamily() {
		return this->family;
	}
	string getName() {
		return this->name;
	}
	string getList() {
		return this->list;
	}
};