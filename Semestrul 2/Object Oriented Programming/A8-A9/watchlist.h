#pragma once
#include "movie.h"
#include<vector>
#include<string>
class WatchList {
private:
	std::vector<Movie> watchlist;
public:
	WatchList();
	~WatchList();
	void addMovie();
	void removeMovie();
	void getAll();
};