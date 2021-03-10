#pragma once

#include "Operation.h"

class Addition: public Operation
{
public:
	using Operation::Operation;
	Expression* simplify() override;
	std::string toString() override;
	char symbol() override;
};
