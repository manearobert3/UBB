#include "repository.h"
#include<iostream>
void Repository::addMovie(const Movie& inputtedMovie)
{
    this->movies.add(inputtedMovie);
}

DynamicVector<Movie> Repository::getAll() const
{
    return this->movies;
}

void Repository::printVector() {
    this->movies.printVector();
}

bool Repository::checkAuthenticity(Movie inputtedMovie) {
    return this->movies.checkAuthenticity(inputtedMovie);
}

Movie Repository::getMovieAtIndex(int index)
{
    return this->movies[index];
}



void Repository::remove(Movie inputtedMovie) {
    this->movies.remove(inputtedMovie);
}
void Repository::update(Movie inputtedMovie, Movie newMovie) {
    this->movies.update(inputtedMovie, newMovie);
}

int Repository::getSize() const
{
    return this->movies.getSize();
}

