#pragma once

#include "Addition.h"

#include <sstream>

class Subtraction : public Operation
{
public:
	using Operation::Operation;
	Expression* simplify() override;
	std::string toString() override;
};
