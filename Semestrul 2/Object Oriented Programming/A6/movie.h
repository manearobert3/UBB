#pragma once
#include<string>

class Movie
{
private: 
	std::string title;
	std::string genre;
	int yearOfRelease;
	int likes;
	std::string trailer;

public:
	Movie();
	Movie(const std::string& title, const std::string& genre, int yearOfRelease, int likes, const std::string& trailer);
	friend std::ostream& operator<<(std::ostream& out, const Movie& movie);
	bool operator==(const Movie& other) const;
	//bool operator!=(const Movie& other) const;
	std::string getTitle() const;
	void setTitle(const std::string& title);
	std::string getTrailer() const;
	void setTrailer(const std::string& trailer);
	std::string getGenre() const;
	void setGenre(const std::string& genre);
	int getYearOfRelease() const;
	void setYearOfRelease(const int& yearOfRelease);
	int getLikes() const;
	void setLikes(const int& likes);

};