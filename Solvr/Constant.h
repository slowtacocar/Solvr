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

    const Expression *getConstant() const override;

    const Expression *getNonConstant() const override;

    Expression *copy() const override;

    bool isEqual(const Expression &expression) const override;

    std::vector<const Expression *> allVariables() const override;

    bool contains(const Expression &expression) const override;
};


#endif //SOLVR_CONSTANT_H
