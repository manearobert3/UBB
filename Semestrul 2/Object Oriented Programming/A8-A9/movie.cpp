#include "movie.h"
#include <iostream>
#include <string>
#include<string.h>
#include<sstream>
Movie::Movie() : title{""}, genre{""}, likes{0}, yearOfRelease{0}, trailer{ "" } {}

Movie::Movie(const std::string& _title,
	const std::string& _genre,
	int _likes,
	int _yearOfRelease,
	const std::string& _trailer) : title{ _title },
	genre{ _genre },
	likes{ _likes },
	yearOfRelease{ _yearOfRelease },
	trailer{ _trailer }
{}

bool Movie::operator==(const Movie & other) const
{
	if (getTitle().compare(other.getTitle())) return false;
	if (getGenre().compare(other.getGenre())) return false;
	if (getTrailer().compare(other.getTrailer())) return false;
	if (likes!=other.getLikes()) return false;
	if (yearOfRelease!=other.getYearOfRelease()) return false;
	return true;
}
//
//std::ostream& operator<<(std::ostream& out, const Movie& movie) {
//	out << movie.getTitle() << ", " << movie.getGenre() << ", " << movie.getYearOfRelease() << ", " << movie.getLikes() << ", " << movie.getTrailer() << std:: endl; return out; }

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
	os << movie.getTitle() << "," << movie.getGenre() << "," << movie.getLikes()<<","<<movie.getYearOfRelease()<<","<<movie.getTrailer()<<"\n";
	return os;
}
std::istream& operator>>(std::istream& is, Movie& movie) {
	std::string movieString;
	std::string object;
	if(std::getline(is, movieString)){
		// Create a string stream to split the line into separate values
		std::stringstream line(movieString);
		std::getline(line, object, ',');
		movie.title = object;
		std::getline(line, object, ',');
		movie.genre = object;
		std::getline(line, object, ',');
		movie.likes = stoi(object);
		std::getline(line, object, ',');
		movie.yearOfRelease = stoi(object);
		std::getline(line, object, ',');
		movie.trailer = object;
		return is;
}
	return is;
}


std::string Movie::getTitle() const
{
	return this->title;
}

void Movie::setTitle(const std::string& title)
{
	this->title = title;
}

std::string Movie::getGenre() const
{
	return this->genre;
}

void Movie::setGenre(const std::string& genre)
{
	this->genre = genre;
}

std::string Movie::getTrailer() const
{
	return this->trailer;
}

void Movie::setTrailer(const std::string& trailer)
{
	this->trailer = trailer;
}

int Movie::getLikes() const
{
	return this->likes;
}

void Movie::setLikes(const int& likes)
{
	this->likes = likes;
}

int Movie::getYearOfRelease() const
{
	return this->yearOfRelease;
}

void Movie::setYearOfRelease(const int& yearOfRelease)
{
	this->yearOfRelease = yearOfRelease;
}