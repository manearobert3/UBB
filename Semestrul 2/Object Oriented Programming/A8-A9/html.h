#pragma once
#include "sendtofile.h"
#include <string>

class HTMLFile : public SendToFile {
public:
	void printSpecificFile() override;
	void displayMovies() const override;


};