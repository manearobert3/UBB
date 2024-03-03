#include "repository.h"
#include<iostream>
#include<algorithm>

Repository::Repository()
{
    this->movies = std::vector<Movie>();
}

Repository::~Repository()
{   
}
void Repository::addMovie(const Movie& inputtedMovie)
{
        this->movies.push_back(inputtedMovie);
}

std::vector<Movie> Repository::getAll() const
{
    return this->movies;
}

//void Repository::printVector() {
//    this->movies.printVector();
//}

bool Repository::checkAuthenticity(Movie inputtedMovie) {
    std::vector<Movie>::iterator it;
    it = std::find(this->movies.begin(), this->movies.end(), inputtedMovie);
    if (it != this->movies.end())
        return true;
    return false;
}

Movie Repository::getMovieAtIndex(int index)
{
    return this->movies[index];
}



void Repository::remove(Movie inputtedMovie) {
    std::vector<Movie>::iterator index;
    index = std::find(this->movies.begin(), this->movies.end(), inputtedMovie);
    this->movies.erase(index);

}
void Repository::update(Movie inputtedMovie, Movie newMovie) {
    std::vector<Movie>::iterator index;
    if (checkAuthenticity(inputtedMovie) == true) {
        std::replace(this->movies.begin(), this->movies.end(), inputtedMovie, newMovie);
    }
}

int Repository::getSize() const
{
    return this->movies.size();
}

