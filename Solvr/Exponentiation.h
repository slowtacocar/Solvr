#pragma once

#include "Addition.h"
#include "Multiplication.h"

#include <sstream>
#include <cmath>

class Exponentiation : public Operation
{
public:
	using Operation::Operation;
	Expression* simplify() override;
	std::string toString() override;
	char symbol() override;
};
