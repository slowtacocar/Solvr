#include "Constant.h"

Constant::Constant()
{
	value = 0;
}

Constant::Constant(double value)
{
	this->value = value;
}

std::string Constant::toString()
{
	if (value >= 0) return std::to_string(value);
	return "(" + std::to_string(value) + ")";
}

double Constant::getValue()
{
	return value;
}

void Constant::setValue(double value)
{
	this->value = value;
}

char Constant::symbol()
{
	return '0';
}

Constant* Constant::getConstant()
{
	return this;
}

Expression* Constant::getNonConstant()
{
	return nullptr;
}
