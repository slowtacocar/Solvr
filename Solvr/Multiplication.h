//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_MULTIPLICATION_H
#define SOLVR_MULTIPLICATION_H


#include "Addition.h"

#include <sstream>

class Multiplication : public Operation {
public:
    using Operation::Operation;

    Expression *simplify() override;

    std::string toString() override;

    char symbol() override;

    Expression* copy() override;
};


#endif //SOLVR_MULTIPLICATION_H
