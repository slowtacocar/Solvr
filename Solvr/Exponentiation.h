//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_EXPONENTIATION_H
#define SOLVR_EXPONENTIATION_H


#include <string>
#include "BinaryOperation.h"
#include "Expression.h"

class Exponentiation : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    Expression *simplify() const override;

    std::string toString() const override;

    char symbol() const override;

    Expression *copy() const override;

    bool isEqual(const Expression &expression) const override;
};


#endif //SOLVR_EXPONENTIATION_H
