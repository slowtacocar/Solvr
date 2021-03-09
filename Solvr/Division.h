#pragma once

#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"

#include <sstream>

class Division : public Operation
{
public:
	using Operation::Operation;
	Expression* simplify() override;
	std::string toString() override;
};
