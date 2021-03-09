#include "Addition.h"

Expression* Addition::simplify()
{
	Expression* simplified1 = getOperand1()->simplify();
	Expression* simplified2 = getOperand2()->simplify();
	if (Constant* constant1 = dynamic_cast<Constant*>(simplified1))
	{
		if (Constant* constant2 = dynamic_cast<Constant*>(simplified2))
		{
			return new Constant(constant1->getValue() + constant2->getValue());
		}
	}
	return new Addition(simplified1, simplified2);
}

std::string Addition::toString()
{
	return getOperand1()->toString() + "+" + getOperand2()->toString();
}
