#pragma once
#include "repository.h"
#include<iostream>
#include<string>
class SendToFile : public Repository
{
protected:
		std::string filename;

public:
	SendToFile();
	virtual ~SendToFile() {}
	void setName(const std::string& name);
	virtual void printSpecificFile() = 0;	
	virtual void displayMovies() const = 0;
};