#include "html.h"
#include<fstream>
#include<Windows.h>

using namespace std;


void HTMLFile::printSpecificFile()
{
	ofstream f(this->filename);
	f << "<!DOCTYPE html>\n<html>\n<head>\n<title>Movies</title>\n</head>\n<body>\n<table border=""5"">\n";
	if (!f.is_open())
		throw exception("The file cannot be opened");

	for (auto movie : this->movies)
	{
		f << "\t<tr>\n";
		f<<"\t\t<td>"<<movie.getGenre()<<"</td>\n";
		f << "\t\t<td>" << movie.getTitle() << "</td>\n";
		f << "\t\t<td>" << movie.getLikes() << "</td>\n";
		f << "\t\t<td>" << movie.getYearOfRelease() << "</td>\n";
		f << "\t\t<td><a href=""" << movie.getTrailer() << """>Link</a></td>\n";
		f << "\t</tr>\n";
	}
	f << "<</table>\n</body>\n</html>";
	f.close();
}

void HTMLFile::displayMovies() const
{
	std::string command = "start " + filename;
	system(command.c_str());
}
