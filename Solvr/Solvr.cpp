#include "Solvr.h"

Expression* parseExpression(std::string string, int start, int stop)
{
	if (start + 1 == stop && std::isalpha(string[start]))
	{
		return new Variable(string[start]);
	}
	int openParens = 0;
	int closeParens = 0;
	char add = 0;
	char mult = 0;
	bool exp = false;
	int lastAdd;
	int lastMult;
	int lastExp;
	bool allDigits = true;
	double constant = 0;
	double multiplier = 1;
	if (string[start] == '(' && string[stop - 1] == ')')
	{
		start++;
		stop--;
	}
	for (int i = start; i < stop; i++)
	{
		if (std::isdigit(string[i]))
		{
			if (multiplier == 1) constant *= 10;
			constant += (string[i] - '0') * multiplier;
			if (multiplier < 1) multiplier /= 10;
		}
		else if (string[i] == '.') multiplier = 0.1;
		else
		{
			if (string[i] == '(') openParens++;
			else if (string[i] == ')') closeParens++;
			else
			{
				allDigits = false;
				if (string[i] == '+' && openParens == closeParens)
				{
					lastAdd = i;
					add = '+';
				}
				else if (string[i] == '-' && openParens == closeParens)
				{
					lastAdd = i;
					add = '-';
				}
				else if (string[i] == '*' && openParens == closeParens)
				{
					lastMult = i;
					mult = '*';
				}
				else if (string[i] == '/' && openParens == closeParens)
				{
					lastMult = i;
					mult = '/';
				}
				else if (!exp && string[i] == '^' && openParens == closeParens)
				{
					lastExp = i;
					exp = true;
				}
			}
		}
	}
	if (allDigits && openParens == closeParens) return new Constant(constant);
	if (add != 0)
	{
		if (add == '+') return new Addition(parseExpression(string, start, lastAdd), parseExpression(string, lastAdd + 1, stop));
		return new Subtraction(parseExpression(string, start, lastAdd), parseExpression(string, lastAdd + 1, stop));
	}
	if (mult != 0)
	{
		if (mult == '*') return new Multiplication(parseExpression(string, start, lastMult), parseExpression(string, lastMult + 1, stop));
		return new Division(parseExpression(string, start, lastMult), parseExpression(string, lastMult + 1, stop));
	}
	if (exp)
	{
		return new Exponentiation(parseExpression(string, start, lastExp), parseExpression(string, lastExp + 1, stop));
	}
	throw BadExpression();
}

int main()
{
	std::string input;
	bool running = true;
	std::cout << "Welcome to Solvr. Type exit to quit." << std::endl;
	while (running)
	{
		std::cout << ">>";
		std::cin >> input;

		if (input == "exit")
		{
			running = false;
		}
		else
		{
			try
			{
				Expression* exp = parseExpression(input, 0, input.length());
				std::cout << exp->toString() << "=";
				Expression* result = exp->simplify();
				std::cout << result->toString() << std::endl;
			}
			catch (BadExpression e)
			{
				std::cout << e.what() << std::endl;
			}
			std::cout << std::endl;
		}
	}
	return 0;
}
