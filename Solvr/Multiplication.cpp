#include "Multiplication.h"

Expression* Multiplication::simplify()
{
	Expression* simplified1 = getOperand1()->simplify();
	Expression* simplified2 = getOperand2()->simplify();
	if (Constant* constant1 = dynamic_cast<Constant*>(simplified1))
	{
		if (Constant* constant2 = dynamic_cast<Constant*>(simplified2))
		{
			return new Constant(constant1->getValue() * constant2->getValue());
		}
	}
	return new Multiplication(simplified1, simplified2);
}

std::string Multiplication::toString()
{
	std::ostringstream os;
	if (dynamic_cast<Addition*>(getOperand1()) || dynamic_cast<Subtraction*>(getOperand1()))
	{
		os << "(" << getOperand1()->toString() << ")";
	}
	else
	{
		os << getOperand1()->toString();
	}
	os << "*";
	if (dynamic_cast<Addition*>(getOperand2()) || dynamic_cast<Subtraction*>(getOperand2()))
	{
		os << "(" << getOperand2()->toString() << ")";
	}
	else
	{
		os << getOperand2()->toString();
	}
	return os.str();
}
