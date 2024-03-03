#pragma once
#include "sendtofile.h"
#include <string>

class CSVFile : public SendToFile {
public:
	void printSpecificFile() override;
	void displayMovies() const override;


};