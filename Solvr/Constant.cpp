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
	return std::to_string(value);
}

double Constant::getValue()
{
	return value;
}

void Constant::setValue(double value)
{
	this->value = value;
}