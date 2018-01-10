

#include "stdafx.h"

#include "exceptions.h"

const char* IOException::what() const throw()
{
	if (this->filename.empty())
		return "Error while processing file";
	std::string message = "Error while process \"" + this->filename + "\" file";
	return message.c_str();
}

HeaderFormatException::HeaderFormatException(const std::string& message)
{
	this->message = message;
}

const char* HeaderFormatException::what() const throw()
{
	return this->message.c_str();
}
