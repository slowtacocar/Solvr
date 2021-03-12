//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_MULTIPLICATION_H
#define SOLVR_MULTIPLICATION_H


#include "Addition.h"
#include "Exponentiation.h"

#include <sstream>

class Multiplication : public Operation {
public:
    using Operation::Operation;

    Expression *simplify() const override;

    std::string toString() const override;

    char symbol() const override;

    Expression* copy() const override;

    std::vector<Expression *> getPowers() const;

    bool isEqual(Expression &expression) const override;
};


#endif //SOLVR_MULTIPLICATION_H
