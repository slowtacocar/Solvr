#pragma once

#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"

#include <sstream>
#include <cmath>

class Exponentiation : public Operation
{
public:
	using Operation::Operation;
	Expression* simplify() override;
	std::string toString() override;
};
