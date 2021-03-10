#include "Variable.h"

Variable::Variable(char letter)
{
	this->letter = letter;
}

std::string Variable::toString()
{
	return std::string(1, letter);
}

char Variable::getLetter()
{
	return letter;
}

char Variable::symbol()
{
	return 'a';
}

Constant* Variable::getConstant()
{
	return nullptr;
}

Expression* Variable::getNonConstant()
{
	return this;
}
