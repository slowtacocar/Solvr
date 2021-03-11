//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_EXPONENTIATION_H
#define SOLVR_EXPONENTIATION_H


#include "Addition.h"
#include "Multiplication.h"
#include "Constant.h"

#include <sstream>
#include <cmath>

class Exponentiation : public Operation {
public:
    using Operation::Operation;

    Expression *simplify() override;

    std::string toString() override;

    char symbol() override;
};


#endif //SOLVR_EXPONENTIATION_H
