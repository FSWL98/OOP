#pragma once
#include <string>
#include <exception>

class IOException : public std::exception
{
public:
	IOException() = default;
	explicit IOException(const std::string& filename)
	{
		this->filename = filename;
	}
	const char* what() const throw() override;

private:
	std::string filename;

};

class HeaderFormatException : public std::exception
{
public:
	HeaderFormatException() = default;
	explicit HeaderFormatException(const std::string& message);
	const char* what() const throw() override;
private:
	std::string message = "WAV header format is invalid";
};

