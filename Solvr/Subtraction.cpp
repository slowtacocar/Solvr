#include "Subtraction.h"

Expression* Subtraction::simplify()
{
	Expression* simplified1 = getOperand1()->simplify();
	Expression* simplified2 = getOperand2()->simplify();
	if (Constant* constant1 = dynamic_cast<Constant*>(simplified1))
	{
		if (Constant* constant2 = dynamic_cast<Constant*>(simplified2))
		{
			return new Constant(constant1->getValue() - constant2->getValue());
		}
	}
	return new Subtraction(simplified1, simplified2);
}

std::string Subtraction::toString()
{
	std::ostringstream os;
	os << getOperand1()->toString() << "-";
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
