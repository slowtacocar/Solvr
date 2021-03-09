#pragma once

#include "Expression.h"

#include <vector>

class Operation: public Expression
{
private:
	Expression* operand1;
	Expression* operand2;

public:
	Operation(Expression* operand1, Expression* operand2);
	Expression* getOperand1();
	Expression* getOperand2();
};
