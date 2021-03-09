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
