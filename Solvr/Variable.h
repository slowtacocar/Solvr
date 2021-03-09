#pragma once

#include "Expression.h"

#include <string>

class Variable: public Expression
{
private:
	char letter;

public:
	Variable(char letter);
	std::string toString() override;
	char getLetter();
};
