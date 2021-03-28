//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_CONSTANT_H
#define SOLVR_CONSTANT_H


#include <string>
#include <vector>
#include "Expression.h"

class Constant : public Expression {
private:
    double value;

public:
    Constant();

    explicit Constant(double value);

    std::string toString() const override;

    double getValue() const;

    char symbol() const override;

    Expression *getConstant() override;

    Expression *getNonConstant() override;

    Expression *copy() const override;

    bool isEqual(Expression &expression) const override;

    std::vector<Expression *> allVariables() override;

    bool contains(Expression &expression) const override;
};


#endif //SOLVR_CONSTANT_H
