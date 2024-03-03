#include "service.h"
#include "movie.h"
#include <string.h>
#include "sendtofile.h"
#include "RepositoryException.h"
Service::Service(Repository& _repo/*, Repository* pointerRepo*/) : repo{ _repo }/*, pointerRepo{ pointerRepo }*/
{
}

void Service::addMovie(const Movie& inputtedMovie)
{
	if (this->repo.checkAuthenticity(inputtedMovie) == false)
		this->repo.addMovie(inputtedMovie);
	else throw DuplicateMovieException();
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

void Service::readFromFileServ(const std::string& file) {
	this->repo.readFromFile(file);

}

void Service::saveToFileServ(const std::string& file) {
	this->repo.writeToFile(file);

}

//void Service::saveToFileServ(const std::string& file) {
//	this->pointerRepo = &this->repo;
//	this->pointerRepo->writeToFile();
//	
//}

bool Service::checkAuthenticity(const Movie& inputtedMovie)
{
	if (this->repo.checkAuthenticity(inputtedMovie) == true)
		return true;
	else return false;
}

int Service::getSize() const
{
	return this->repo.getSize();
}

Movie Service::getMovieAtIndex(int index) 
{
	return this->repo.getMovieAtIndex(index);
}