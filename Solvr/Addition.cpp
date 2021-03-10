#include "Addition.h"

Expression* Addition::simplify()
{
	Expression* simplified1 = getOperand1()->simplify();
	Expression* simplified2 = getOperand2()->simplify();	
	if (simplified1->symbol() == '0' && simplified2->symbol() == '0')
	{
		return new Constant(simplified1->getConstant()->getValue() + simplified2->getConstant()->getValue());
	}
	if (simplified1->symbol() == '0' && simplified2->symbol() == '+' && simplified2->getConstant())
	{
		Constant* constant = new Constant(simplified1->getConstant()->getValue() + simplified2->getConstant()->getValue());
		if (constant->getValue() != 0) return new Addition(constant, simplified2->getNonConstant());
		return simplified2->getNonConstant();
	}
	if (simplified1->symbol() == '+' && simplified1->getConstant() && simplified2->symbol() == '0')
	{
		Constant* constant = new Constant(simplified1->getConstant()->getValue() + simplified2->getConstant()->getValue());
		if (constant->getValue() != 0) return new Addition(constant, simplified1->getNonConstant());
		return simplified1->getNonConstant();
	}
	if (simplified1->symbol() == '+' && simplified1->getConstant() && simplified2->symbol() == '+' && simplified2->getConstant())
	{
		Constant* constant = new Constant(simplified1->getConstant()->getValue() + simplified2->getConstant()->getValue());
		if (constant->getValue() != 0) return new Addition(constant, Addition(simplified1->getNonConstant(), simplified2->getNonConstant()).simplify());
		return Addition(simplified1->getNonConstant(), simplified2->getNonConstant()).simplify();
	}
	return new Addition(simplified1, simplified2);
}

std::string Addition::toString()
{
	return getOperand1()->toString() + "+" + getOperand2()->toString();
}

char Addition::symbol()
{
	return '+';
}
