#pragma once

#include "Addition.h"
#include "Multiplication.h"
#include "Exponentiation.h"
#include "Variable.h"

#include <iostream>

Constant* readDigits(std::string string, size_t start, size_t stop);
Expression* parseExpression(std::string string, size_t start, size_t stop);
