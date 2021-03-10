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

Constant* Operation::getConstant()
{
	if (operand1->symbol() == '0') return dynamic_cast<Constant*>(operand1);
	if (operand2->symbol() == '0') return dynamic_cast<Constant*>(operand2);
	return nullptr;
}

Expression* Operation::getNonConstant()
{
	if (operand1->symbol() != 0 && operand2->symbol() != 0) return this;
	if (operand1->symbol() != '0') return operand1;
	if (operand2->symbol() != '0') return operand2;
	return nullptr;
}


