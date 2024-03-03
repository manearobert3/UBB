#pragma once
#include "repository.h"

class Service
{
private:
	Repository repo;
public:

	//Service();
	//~Service() {  };
	void addMovie(const Movie& inputedMovie);
	int getSize() const;
	void updateMovie(const Movie& inputtedMovie, Movie& newMovie);
	void removeMovie(const Movie& inputtedMovie);
	void saveToFileServ(const std::string& file);
	std::vector<Movie> getAll() const;
	Movie getMovieAtIndex(int index);
	bool checkAuthenticity(const Movie& inputedMovie);
	void readFromFileServ(const std::string& file);

};


