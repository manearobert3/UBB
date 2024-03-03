#pragma once
#include "repository.h"

class Service
{
private:
	Repository& repo;

public:
	Service(Repository& _repo);
	void addMovie(const Movie& inputedMovie);
	int getSize() const;
	void updateMovie(const Movie& inputtedMovie, Movie& newMovie);
	void removeMovie(const Movie& inputtedMovie);
	void printMovies();
	Movie getMovieAtIndex(int index);
	bool checkAuthenticity(const Movie& inputedMovie);
};


