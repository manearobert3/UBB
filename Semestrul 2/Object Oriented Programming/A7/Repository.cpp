#include "repository.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include"RepositoryException.h"
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
void Repository::readFromFile(const std::string filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Movie movie;
    std::string movieString;
    while (file>>movie)
        //while (std::getline(file , movieString))
       // movieString >> movie;
        this->movies.push_back(movie);

    file.close();
}

void Repository::writeToFile(const std::string filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Movie movie;
    std::string movieString;
    for (auto movie : movies)
    {
        file << movie;

    }

    file.close();
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
