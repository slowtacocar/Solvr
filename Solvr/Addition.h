//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_ADDITION_H
#define SOLVR_ADDITION_H


#include "Operation.h"
#include "Constant.h"
#include "Multiplication.h"

#include <utility>

class Addition : public Operation {
public:
    using Operation::Operation;

    Expression *simplify() const override;

    std::string toString() const override;

    char symbol() const override;

    Expression* copy() const override;

    std::vector<Expression *> getTerms() const;

    bool isEqual(Expression &expression) const override;
};


#endif //SOLVR_ADDITION_H
