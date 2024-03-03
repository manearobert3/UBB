#include "service.h"
#include "movie.h"
#include <string.h>
Service::Service(Repository& _repo) : repo{ _repo }
{
}

void Service::addMovie(const Movie& inputtedMovie)
{
	this->repo.addMovie(inputtedMovie);
}

void Service::updateMovie(const Movie& inputtedMovie,Movie& newMovie)
{
	this->repo.update(inputtedMovie,newMovie);
}

void Service::removeMovie(const Movie& inputtedMovie)
{
	this->repo.remove(inputtedMovie);
}

std::vector<Movie> Service::getAll() const
{
	return this->repo.getAll();
}

//void Service::printMovies() {
//	this->repo.printVector();
//}

bool Service::checkAuthenticity(const Movie& inputtedMovie)
{
	return this->repo.checkAuthenticity(inputtedMovie);
}

int Service::getSize() const
{
	return this->repo.getSize();
}

Movie Service::getMovieAtIndex(int index) 
{
	return this->repo.getMovieAtIndex(index);
}