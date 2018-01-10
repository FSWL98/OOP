#pragma once
#include <exception>
#include <string>


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