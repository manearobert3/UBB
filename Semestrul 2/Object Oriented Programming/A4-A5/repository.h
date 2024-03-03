#pragma once
#include "DynamicVector.h"

class Repository
{
private:
	DynamicVector<Movie> movies;

public:
	void addMovie(const Movie& inputtedMovie);
	DynamicVector<Movie> getAll() const;
	int getSize() const;
	void printVector();
	void update(Movie availableMovie, Movie newMovie);
	bool checkAuthenticity(Movie inputtedMovie);
	Movie getMovieAtIndex(int index);


	void remove(Movie inputtedMovie);

};
