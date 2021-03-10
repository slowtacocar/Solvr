#pragma once

#include "Expression.h"

class Constant: public Expression
{
private:
	double value;

public:
	Constant();
	Constant(double value);
	std::string toString() override;
	double getValue();
	void setValue(double value);
	char symbol() override;
	Constant* getConstant() override;
	Expression* getNonConstant() override;
};
