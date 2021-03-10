#pragma once

#include "Constant.h"

#include <string>

class Expression
{
public:
	virtual Expression* simplify();
	virtual std::string toString() = 0;
	virtual char symbol() = 0;
	virtual Constant* getConstant() = 0;
	virtual Expression* getNonConstant() = 0;
};
