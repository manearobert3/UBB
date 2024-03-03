#include <iostream>
#include <windows.h>
#include <string>
#include "Header.h"
#include <crtdbg.h>
#include "service.h"
#include "UI.h"
#include <cstdlib>
#include "sendtofile.h"
#include "CSVFile.h"
#include "html.h"
#include "movieValidator.h"
#include "RepositoryException.h"
#include "FakeRepository.h"
#include<assert.h>
void UI::mainProgram()
{
	testFakeRepo();
	SendToFile* watchlist = new CSVFile{};
	//initialiseDatabase();
	std::string typeWatchListFormat;
	std::string name;
	while (true)
	{
		std::string typeWatchListFormat;
		printMainProgramOptions();
		std::string optionMode;
		std::cin >> optionMode;
		std::string filename;
		bool exitStatus = false;
		while (exitStatus == false) {
			std::cout << "Filename from which to read the movies?";
			try {
				std::cout << "Input the file name" << std::endl;
				std::cin >> name;
				this->service.readFromFileServ(name);
				exitStatus = true;
			}
			catch (FileException& exception)
			{
				std::cout << exception.what() << "\n";
			}
		}
		exitStatus = false;
		while (exitStatus == false) {
			try {
				std::cout << "CSV or HTML? (<csv> or <html>)";
				std::cin >> typeWatchListFormat;
				if (typeWatchListFormat == "csv")
				{
					watchlist = new CSVFile{};
					watchlist->setName("moviescsv.csv");
					watchlist->printSpecificFile();
					exitStatus = true;
				}
				if (typeWatchListFormat == "html")
				{
					watchlist = new HTMLFile{};
					watchlist->setName("movieshtml.html");
					watchlist->printSpecificFile();
					exitStatus = true;
				}
				else if (typeWatchListFormat != "html" and typeWatchListFormat != "csv")
					std::cout << "Not a valid command\n";
			}
			catch (FileException& exception)
			{
				std::cout << exception.what() << "\n";
			}
		}
		if (optionMode == "admin")
		{
			bool exitValid = false;
			while (exitValid == false) {
				printAdminProgramOptions();
				std::string optionAdmin;
				std::cin >> optionAdmin;

				if (optionAdmin == "add") {
					addMovieRepo();
					this->service.saveToFileServ(name);
					continue;
				}
				else if (optionAdmin == "update") {
					updateMovieRepo();
					this->service.saveToFileServ(name);
					continue;
				}
				else if (optionAdmin == "delete") {
					removeMovieRepo();
					this->service.saveToFileServ(name);
					continue;
				}
				else if (optionAdmin == "print") {
					printMovies();
					//watchlist->displayMovies();
					//watchlist->printSpecificFile();
					continue;
				}
				else if (optionAdmin == "save") {
					try {
					std::cout << "filename?";
					std::cin >> filename;
					this->service.saveToFileServ(filename);
					continue;
				}
					catch (FileException& exception)
					{
						std::cout << exception.what() << "\n";
					}
				}
				else if (optionAdmin == "exit") {
					exitValid = true;
				}
				else
					std::cout << "Not a valid command!\n";
			}
		}
		if (optionMode == "user") {
			bool exitVariable = false;
			while (exitVariable == false)
			{
				std::string genreInputted;
				Movie currentMovie;
				bool verifyExistenceGenre = false;
				int index = 0;
				int indexVerifying = 0;
				std::cout << "Input the genre for the movies or <null> for all movies: " << std::endl;
				while (verifyExistenceGenre == false and genreInputted != "null") {
					std::cin >> genreInputted;
					indexVerifying = 0;
					while (indexVerifying < this->service.getSize())
					{
						if (this->service.getMovieAtIndex(indexVerifying).getGenre() == genreInputted)
						{
								verifyExistenceGenre = true;
						}
						indexVerifying++;
					}
					if (verifyExistenceGenre == false and genreInputted != "null") {
						std::cout << "Not valid genre input again: \n";
					}
				}
				while (index < this->service.getSize())
				{
					if (genreInputted == "null") {

						currentMovie = this->service.getMovieAtIndex(index);
					}
					else
					{
						while (this->service.getMovieAtIndex(index).getGenre() != genreInputted and index < this->service.getSize()) {
							index++;
							if (index >= this->service.getSize())
							{
								index = 0;
							}
						}
					}
					currentMovie = this->service.getMovieAtIndex(index);
					explicitMoviePrint(currentMovie);
					std::string command = "start " + currentMovie.getTrailer();
					system(command.c_str());
					printUserProgramOptions();
					std::string optionUser;
					std::cin >> optionUser;
					if (optionUser == "like") {
						currentMovie.setLikes(currentMovie.getLikes() + 1);
						this->service.updateMovie(this->service.getMovieAtIndex(index), currentMovie);
						std::string optionUserLike;
						std::cout << "Want to add movie to watch list? <yes> or <no>: ";
						std::cin >> optionUserLike;
						if (optionUserLike != "yes" and optionUserLike != "no")
							std::cout << "not a valid command" << std::endl;
						else
						{
							if (optionUserLike == "yes") {
								try {
									if (watchlist->checkAuthenticity(currentMovie) == false)
									{
										watchlist->addMovie(currentMovie);
										watchlist->printSpecificFile();
									}
									else
										throw DuplicateMovieException();
								}
								catch (DuplicateMovieException& exception) {
									std::cout << exception.what() << "\n";
								}
							}
						}
					}
					if (optionUser == "delete") {
						try {
							if (watchlist->checkAuthenticity(currentMovie) == true)
							{
								watchlist->remove(currentMovie);
								watchlist->printSpecificFile();
							}
							else
								throw InexistentMovieException();
						}
						catch (InexistentMovieException& exception) {
							std::cout << exception.what() << "\n";
						}
					}
					if (optionUser == "next")
					{
						index++;
						if (index == this->service.getSize())
							index = 0;
					}

					if (optionUser == "print")
					{printMoviesCustom(*watchlist);
					watchlist->printSpecificFile();
					watchlist->displayMovies();
				}

						if (optionUser == "exit")
						{
							index = this->service.getSize() + 5;
							exitVariable = true;
						}


					


				}

			}
		}

		if (optionMode == "exit")
			std::exit(0);
		else if (optionMode!="exit" && optionMode!="user" && optionMode!="admin")
			std::cout << "Not a valid command\n";
	}
		}
	
void UI::testFakeRepo() {

	auto* repoToBeTested = new FakeRepository{};
	Service serviceToBeTested;
	repoToBeTested->checkPresenceOfEntity = true;
	Movie movie{ "The Shawshank Redemption","Drama",44345,1994,"https://www.youtube.com/watch?v=6hB3S9bIaco" };
	assert(serviceToBeTested.checkAuthenticity(movie));
	repoToBeTested->checkPresenceOfEntity = false;
	assert(!serviceToBeTested.checkAuthenticity(movie));
}


void UI::saveToFile()
{
	std::string name;
	std::cout << "Input the file name" << std::endl;
	std::cin >> name;

}

void UI::readFromFile() {
	std::string name;
	std::cout << "Input the file name" << std::endl;
	std::cin >> name;
	this->service.readFromFileServ(name);
}




void UI::initialiseDatabase() {
	Movie movie{ "The Shawshank Redemption","Drama",44345,1994,"https://www.youtube.com/watch?v=6hB3S9bIaco" };
	this->service.addMovie(movie);
	Movie movie1{ "The Godfather","Drama",25123,1972,"https://www.youtube.com/watch?v=sY1S34973zA" };
	this->service.addMovie(movie1);
	Movie movie2{ "The Dark Knight","Action",18640,2008,"https://www.youtube.com/watch?v=EXeTwQWrcwY" };
	this->service.addMovie(movie2);
	Movie movie3{ "The Godfather Part 2","Drama",15343,1974,"https://www.youtube.com/watch?v=9O1Iy9od7-A" };
	this->service.addMovie(movie3);
	Movie movie4{ "The Lord of the Rings: The Return of the King","Adventure",28789,2003,"https://www.youtube.com/watch?v=r5X-hFf6Bwo" };
	this->service.addMovie(movie4);
	Movie movie5{ "The Lord of the Rings: The Fellowship of the Ring","Adventure",31529,2001,"https://www.youtube.com/watch?v=V75dMMIW2B4" };
	this->service.addMovie(movie5);
	Movie movie6{ "Fight Club","Drama",18793,1999,"https://www.youtube.com/watch?v=SUXWAEX2jlg" };
	this->service.addMovie(movie6);
	Movie movie7{ "Inception","Action",16163,2010,"https://www.youtube.com/watch?v=8hP9D6kZseM" };
	this->service.addMovie(movie7);
	Movie movie8{ "The Matrix","Action",25873,1999,"https://www.youtube.com/watch?v=vKQi3bBA1y8" };
	this->service.addMovie(movie8);
	Movie movie9{ "Star Wars: Episode V - The Empire Strikes Back","Adventure",17105,1980,"https://www.youtube.com/watch?v=JNwNXF9Y6kY" };
	this->service.addMovie(movie9);

}

void UI::explicitMoviePrint(Movie& movie) {
	std::cout << "Title is:" << movie.getTitle() << std::endl;
	std::cout << "Genre is:" << movie.getGenre() << std::endl;
	std::cout << "Number of likes are:" << movie.getLikes() << std::endl;
	std::cout << "Year of release is:" << movie.getYearOfRelease() << std::endl;
}

void UI::printUserProgramOptions() {
	std::cout << "<like>: Like the movie" << std::endl;
	std::cout << "<delete>: Delete movie from watch list" << std::endl;
	std::cout << "<next>: Next movie" << std::endl;
	std::cout << "<print>: Print watch list" << std::endl;
	std::cout << "<exit>: Exit" << std::endl;
}

void UI::printMainProgramOptions() {
	std::cout << "Type <admin> for administrator mode or <user> for user mode or <exit> to exit: ";
}

void UI::printAdminProgramOptions() {
	std::cout << "<add>: Add movie" << std::endl;
	std::cout << "<delete>: Delete movie" << std::endl;
	std::cout << "<update>: Update movie" << std::endl;
	std::cout << "<print>: Print database of movies" << std::endl;
	std::cout << "<save>: To save current database of movies to a specified file" << std::endl;
	std::cout << "<exit>: Exit" << std::endl;
}

void UI::addMovieRepo()
{
	Movie movie;
	std::string title;
	std::string genre;
	std::string yearOfRelease;
	std::string likes;
	std::string trailer;
	std::cout << "Trailer:" << std::endl;
	std::cin >> trailer;
	std::cout << "Genre:" << std::endl;
	std::cin >> genre;
	std::cout << "Title:" << std::endl;
	std::cin >> title;
	std::cout << "likes:" << std::endl;
	std::cin >> likes;
	std::cout << "yearOfRelease:" << std::endl;
	std::cin >> yearOfRelease;
	try
	{
		MovieValidator::validate(title, genre, yearOfRelease, likes, trailer);
		movie.setGenre(genre);
		movie.setLikes(std::stoi(likes));
		movie.setYearOfRelease(std::stoi(yearOfRelease));
		movie.setTrailer(trailer);
		movie.setTitle(title);

		try
		{
			//if (this->service.checkAuthenticity(movie) == false) {
				this->service.addMovie(movie);
			//}
			//else if (this->service.checkAuthenticity(movie) == true)
			//	throw DuplicateMovieException();
		}
		catch (DuplicateMovieException& exception)
		{
			std::cout << exception.what() << "\n";
		}
	}
	catch (MovieException& errors)
	{
		for (auto error : errors.getErrors())
			std::cout << error << "\n";
	}

}

void UI::updateMovieRepo()
{
	Movie movieExistent;
	Movie newMovie;
	std::string title, title1;
	std::string genre, genre1;
	std::string yearOfRelease, yearOfRelease1;
	std::string likes, likes1;
	std::string trailer, trailer1;
	std::cout << "Input current movie" << std::endl;
	std::cout << "Trailer:" << std::endl;
	std::cin >> trailer;
	std::cout << "Genre:" << std::endl;
	std::cin >> genre;
	std::cout << "Title:" << std::endl;
	std::cin >> title;
	std::cout << "likes:" << std::endl;
	std::cin >> likes;
	std::cout << "yearOfRelease:" << std::endl;
	std::cin >> yearOfRelease;

	try
	{
		MovieValidator::validate(title, genre, yearOfRelease, likes, trailer);
		movieExistent.setGenre(genre);
		movieExistent.setLikes(std::stoi(likes));
		movieExistent.setYearOfRelease(std::stoi(yearOfRelease));
		movieExistent.setTrailer(trailer);
		movieExistent.setTitle(title);
		try
		{
			if (this->service.checkAuthenticity(movieExistent) == false)
				throw InexistentMovieException();
			else
			{
				std::cout << "Input updated movie" << std::endl;
				std::cout << "Trailer:" << std::endl;
				std::cin >> trailer1;
				std::cout << "Genre:" << std::endl;
				std::cin >> genre1;
				std::cout << "Title:" << std::endl;
				std::cin >> title1;
				std::cout << "likes:" << std::endl;
				std::cin >> likes1;
				std::cout << "yearOfRelease:" << std::endl;
				std::cin >> yearOfRelease1;
				MovieValidator::validate(title1, genre1, yearOfRelease1, likes1, trailer1);
				newMovie.setGenre(genre1);
				newMovie.setLikes(std::stoi(likes1));
				newMovie.setYearOfRelease(std::stoi(yearOfRelease1));
				newMovie.setTrailer(trailer1);
				newMovie.setTitle(title1);
				if (this->service.checkAuthenticity(newMovie) == false)
					throw InexistentMovieException();
				this->service.updateMovie(movieExistent, newMovie);
				std::cout << "Movie updated\n";
			}

		}
		catch (InexistentMovieException& exception)
		{
			std::cout << exception.what() << "\n";
		}
	}
	catch (MovieException& errors)
	{
		for (auto error : errors.getErrors())
			std::cout << error << "\n";
	}
}

void UI::printMovies() {
	std::vector<Movie> movies = this->service.getAll();
	std::cout << "number of movies: " << movies.size() << std::endl;
	std::vector<Movie>::iterator index;
	for (index = movies.begin(); index < movies.end(); index++) {
		Movie currentMovie = *index;
		std::cout << currentMovie.getTrailer() << ", " << currentMovie.getGenre() << ", " << currentMovie.getTitle() << ", " << currentMovie.getLikes() << ", " << currentMovie.getYearOfRelease() << std::endl;
	}
}

void UI::printMoviesCustom(Repository moviesRepo) {
	std::vector<Movie> movies = moviesRepo.getAll();
	std::cout << "number of movies: " << movies.size() << std::endl;
	std::vector<Movie>::iterator index;
	for (index = movies.begin(); index < movies.end(); index++) {
		Movie currentMovie = *index;
		std::cout << currentMovie.getTrailer() << ", " << currentMovie.getGenre() << ", " << currentMovie.getTitle() << ", " << currentMovie.getLikes() << ", " << currentMovie.getYearOfRelease() << std::endl;
	}
}

void UI::removeMovieRepo()
{
	Movie movie;
	std::string title;
	std::string genre;
	std::string yearOfRelease;
	std::string  likes;
	std::string trailer;
	std::cout << "Trailer:" << std::endl;
	std::cin >> trailer;
	std::cout << "Genre:" << std::endl;
	std::cin >> genre;
	std::cout << "Title:" << std::endl;
	std::cin >> title;
	std::cout << "likes:" << std::endl;
	std::cin >> likes;
	std::cout << "yearOfRelease:" << std::endl;
	std::cin >> yearOfRelease;
	try
	{
		MovieValidator::validate(title, genre, yearOfRelease, likes, trailer);
		movie.setGenre(genre);
		movie.setLikes(std::stoi(likes));
		movie.setYearOfRelease(std::stoi(yearOfRelease));
		movie.setTrailer(trailer);
		movie.setTitle(title);
		try
		{
			if (this->service.checkAuthenticity(movie) == true) {
				this->service.removeMovie(movie);
			}
			else if (this->service.checkAuthenticity(movie) == false)
				throw InexistentMovieException();
		}
		catch (InexistentMovieException& exception)
		{
			std::cout << exception.what() << "\n";
		}
	}
	catch (MovieException& errors)
	{
		for (auto error : errors.getErrors())
			std::cout << error << "\n";
	}



}