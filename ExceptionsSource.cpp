#include "stdafx.h"
#include "Exceptions.h"


FileException::FileException(const std::string &filename)
{
	this->filename = filename;
}

const std::string FileException::whats() const throw()
{
	std::string message = "Error while proccessing \"" + this->filename + "\" file";
	return message;
}

NoSuchSectionOrParameterException::NoSuchSectionOrParameterException(const std::string &message)
{
	this->message = message;
}
const std::string NoSuchSectionOrParameterException::whats() const throw()
{
	std::string message = "No section or parameter founded";
	if (this->message.empty())
		return message.c_str();
	message += ": \n" + this->message;
	return message;
}

CantConvertTypeException::CantConvertTypeException(const std::string &message)
{
	this->message = message;
}

const std::string CantConvertTypeException::whats() const throw()
{
	std::string message = "Can't convert types";
	if (this->message.empty())
		return message.c_str();
	message += ": \n" + this->message;
	return message;
}