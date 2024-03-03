#include"CSVFile.h"
#include<fstream>
#include<Windows.h>
#include "RepositoryException.h"
using namespace std;

void CSVFile::printSpecificFile() {
	ofstream file(this->filename, std::ios::out);

	if (!file.is_open())
		throw FileException("The file cannot be opened");

	for (auto movie : this->movies)
		file << movie;

	file.close();
}

void CSVFile::displayMovies() const
{	string filenameString= "\"" + this->filename + "\"";
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", filenameString.c_str(), NULL, SW_SHOWMAXIMIZED);
}