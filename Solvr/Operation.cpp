#include "Operation.h"

Operation::Operation(Expression* operand1, Expression* operand2)
{
	this->operand1 = operand1;
	this->operand2 = operand2;
}

Expression* Operation::getOperand1()
{
	return operand1;
}

Expression* Operation::getOperand2()
{
	return operand2;
}


