#pragma once
#include <exception>
#include <string>

class FileException : std::exception
{
public:
	FileException() = default;
	explicit FileException(const std::string &filename);
	const std::string whats() const throw();
private:
	std::string filename = "";
};

class NoSuchSectionOrParameterException : std::exception
{
public:
	NoSuchSectionOrParameterException() = default;
	explicit NoSuchSectionOrParameterException(const std::string &message);
	const std::string whats() const throw();
private:
	std::string message;

};


class CantConvertTypeException : std::exception
{
public:
	CantConvertTypeException() = default;
	explicit CantConvertTypeException(const std::string &message);
	const std::string whats() const throw();
private:
	std::string message;
};