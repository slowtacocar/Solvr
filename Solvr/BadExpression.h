#pragma once

#include <exception>

class BadExpression: public std::exception
{
public:
	const char* what() const throw();
};
