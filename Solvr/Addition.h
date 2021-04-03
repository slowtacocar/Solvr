//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_ADDITION_H
#define SOLVR_ADDITION_H


#include <string>
#include <vector>
#include "BinaryOperation.h"
#include "Expression.h"

class Addition : public BinaryOperation {
public:
    using BinaryOperation::BinaryOperation;

    Expression *simplify() const override;

    std::string toString() const override;

    char symbol() const override;

    Expression *copy() const override;

    std::vector<Expression *> getTerms() const;

    bool isEqual(const Expression &expression) const override;
};


#endif //SOLVR_ADDITION_H
