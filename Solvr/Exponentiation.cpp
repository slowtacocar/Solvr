#include "Exponentiation.h"

Expression* Exponentiation::simplify()
{
	Expression* simplified1 = getOperand1()->simplify();
	Expression* simplified2 = getOperand2()->simplify();
	if (simplified1->symbol() == '0' && simplified2->symbol() == '0')
	{
		return new Constant(pow(simplified1->getConstant()->getValue(), simplified2->getConstant()->getValue()));
	}
	if (simplified1->symbol() == '0' && simplified1->getConstant()->getValue() == 0) return new Constant();
	if (simplified1->symbol() == '0' && simplified1->getConstant()->getValue() == 1) return new Constant(1);
	if (simplified2->symbol() == '0' && simplified2->getConstant()->getValue() == 0) return new Constant(1);
	if (simplified2->symbol() == '0' && simplified2->getConstant()->getValue() == 1) return simplified1;
	if (simplified1->symbol() == '^')
	{
		Exponentiation* exp = dynamic_cast<Exponentiation*>(simplified1);
		return new Exponentiation(exp->getOperand1(), Multiplication(exp->getOperand2(), simplified2).simplify());
	}
	return new Exponentiation(simplified1, simplified2);
}

std::string Exponentiation::toString()
{
	std::ostringstream os;
	if (getOperand1()->symbol() == '+' || getOperand1()->symbol() == '*' || getOperand1()->symbol() == '^') os << "(" << getOperand1()->toString() << ")";
	else os << getOperand1()->toString();
	os << "^";
	if (getOperand2()->symbol() == '+' || getOperand2()->symbol() == '*') os << "(" << getOperand2()->toString() << ")";
	else os << getOperand2()->toString();
	return os.str();
}

char Exponentiation::symbol()
{
	return '^';
}
