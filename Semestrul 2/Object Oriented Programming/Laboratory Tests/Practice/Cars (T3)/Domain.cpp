#include "Domain.h"
#include <sstream>
#include <string>

string Car::toString()
{
	//std::stringstream s;
	//this->name << ' | ' << this->model << ' | ' << this->color << ' | ' << to_string(this->year);
	return this->name + " | " + this->model + " | " + this->color + " | " + to_string(this->year);
}
