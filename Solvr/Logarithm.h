//
// Created by bobby on 3/27/2021.
//

#ifndef SOLVR_LOGARITHM_H
#define SOLVR_LOGARITHM_H


#include <string>
#include "UnaryOperation.h"
#include "Expression.h"

class Logarithm : public UnaryOperation {
public:
    using UnaryOperation::UnaryOperation;

    Expression *simplify() const override;

    std::string toString() const override;

    char symbol() const override;

    Expression *copy() const override;

    bool isEqual(Expression &expression) const override;
};


#endif //SOLVR_LOGARITHM_H
