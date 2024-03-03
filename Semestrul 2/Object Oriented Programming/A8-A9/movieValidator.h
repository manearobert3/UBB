#pragma once
#include<string>
#include "movie.h"
#include<vector>

class MovieException

{

private:
	std::vector<std::string> errors;

public:
	MovieException(std::vector<std::string> errors);
	std::vector<std::string> getErrors();
};

class MovieValidator {
public:
	MovieValidator() {};
	static void validate(const std::string& titleToValidate, const std::string& genreToValidate,
		const std::string& likesToValidate, const std::string& yearToValidate, const std::string& trailerToValidate);

};