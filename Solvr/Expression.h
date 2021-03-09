#pragma once

#include <string>

class Expression
{
public:
	virtual Expression* simplify();
	virtual std::string toString() = 0;
};
