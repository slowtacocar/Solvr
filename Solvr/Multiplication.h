//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_MULTIPLICATION_H
#define SOLVR_MULTIPLICATION_H


#include <string>
#include <vector>
#include "BinaryOperation.h"
#include "Expression.h"

class Multiplication : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    Expression *simplify() const override;

    std::string toString() const override;

    char symbol() const override;

    Expression *copy() const override;

    std::vector<const Expression *> getPowers() const;

    bool isEqual(const Expression &expression) const override;

    const Expression *findCoefficient(const Expression *variable) const override;
};


#endif //SOLVR_MULTIPLICATION_H
