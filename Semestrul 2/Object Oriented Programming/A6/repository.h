#pragma once
#include<string>
#include<vector>
#include<iostream>
#include"movie.h"
class Repository
{
private:
	std::vector<Movie> movies;

public:
	Repository();
	~Repository();
	void addMovie(const Movie& inputtedMovie);
	std::vector<Movie> getAll() const;
	int getSize() const;
	//void printVector();
	void update(Movie availableMovie, Movie newMovie);
	bool checkAuthenticity(Movie inputtedMovie);
	Movie getMovieAtIndex(int index);
	void remove(Movie inputtedMovie);

};
