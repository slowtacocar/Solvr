#pragma once

#include "Addition.h"

#include <sstream>

class Multiplication : public Operation
{
public:
	using Operation::Operation;
	Expression* simplify() override;
	std::string toString() override;
	char symbol() override;
};
