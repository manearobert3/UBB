#include "movieValidator.h"
#include <iostream>
MovieException::MovieException(std::vector<std::string> errors) : errors{ errors }
{
}

std::vector<std::string> MovieException::getErrors()
{
	return this->errors;
}
//Movie movie{ title,genre,std::stoi(likes),std::stoi(yearOfRelease),trailer };
void MovieValidator::validate(const std::string &titleToValidate, const std::string& genreToValidate, 
	const std::string& likesToValidate, const std::string& yearToValidate, const std::string& trailerToValidate)
{
	std::vector<std::string> errors;
	int numberOfLikes;
	try
	{
		numberOfLikes = std::stoi(likesToValidate);
	}
	catch (std::exception &error)
	{
		errors.push_back("The number of likes must be an integer");
	}

	/*int yearOfRelease;
	try
	{
		yearOfRelease= std::stoi(yearToValidate);
	}
	catch (MovieException& errorCaught)
	{
		for (auto error : errorCaught.getErrors())
			std::cout << error;
	}*/
	int yearOfRelease;
	try
	{
		yearOfRelease = std::stoi(yearToValidate);
		if(yearOfRelease < 0)
			errors.push_back(std::string("The year of release should be a number bigger than 0"));
	}
	catch (std::exception& error)
	{
		errors.push_back(std::string("Year of release must be an integer"));
	}
	if (genreToValidate.empty())
		errors.push_back(std::string("Please input a genre!"));
	if (titleToValidate.empty())
		errors.push_back(std::string("Please input the title of the movie!"));
	std::string::size_type checkWWW = trailerToValidate.find("www");
	std::string::size_type checkHTTP = trailerToValidate.find("http");
	if (checkWWW != 0 && checkHTTP != 0)
		errors.push_back("The youtube source must start with one of the following strings: \"www\" or \"http\"");
	if (errors.size() > 0)
		throw MovieException(errors);
}
