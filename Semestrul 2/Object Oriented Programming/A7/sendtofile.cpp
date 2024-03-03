#include"sendtofile.h"

SendToFile::SendToFile() :Repository{}, filename{""}
{}

void SendToFile::setName(const std::string& name) {
	this->filename = name;
}