#pragma once
#include<string>
#include<vector>
#include<iostream>
#include "movie.h"
class Repository
{
protected:
	std::vector<Movie> movies;

public:
	Repository();
	virtual ~Repository();
	void addMovie(const Movie& inputtedMovie);
	std::vector<Movie> getAll() const;
	int getSize() const;
	//void printVector();
	void update(Movie availableMovie, Movie newMovie);
	virtual bool checkAuthenticity(Movie inputtedMovie);
	Movie getMovieAtIndex(int index);
	void remove(Movie inputtedMovie);


public:
	void readFromFile(const std::string filename);
	void writeToFile(const std::string filename);

};
