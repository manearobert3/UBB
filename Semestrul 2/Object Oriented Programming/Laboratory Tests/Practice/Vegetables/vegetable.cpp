#include "vegetable.h"

string Vegetable::toString()
{
	string s;
	s = this->family + " | " + this->name + " | " + this->list + "\n";
	return s;
}
