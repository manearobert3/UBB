#pragma once
#include "service.h"

class UI

{
private:
	Service service;
public:
	UI(const Service serv) : service(serv) {}
	void mainProgram();
	void adminProgram();
	void userProgram();
private:
	void readFromFile();
	void saveToFile();
	void outputCSV(Repository watchlist);
	void printMoviesCustom(Repository moviesRepo);
	void printMovies();
	void printMainProgramOptions();
	void printAdminProgramOptions();
	void printUserProgramOptions();
	void addMovieRepo();
	void updateMovieRepo();
	void removeMovieRepo();
	void explicitMoviePrint(Movie& movie);
	void initialiseDatabase();
	void testFakeRepo();
};