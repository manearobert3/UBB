#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string message;

public:
	FileException(const std::string& messag);
	virtual const char* what();
};

class RepositoryException : public std::exception
{
protected:
	std::string message;

public:
	RepositoryException();
	RepositoryException(const std::string& messag);
	virtual ~RepositoryException() {}
	virtual const char* what();
};

class DuplicateMovieException : public RepositoryException
{
public:
	const char* what();
};

class InexistentMovieException : public RepositoryException
{
public:
	const char* what();
};