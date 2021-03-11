//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_CONSTANT_H
#define SOLVR_CONSTANT_H


#include "Expression.h"

#include <sstream>

class Constant : public Expression {
private:
    double value;

public:
    Constant();

    explicit Constant(double value);

    std::string toString() override;

    double getValue() const;

    char symbol() override;

    Expression *getConstant() override;

    Expression *getNonConstant() override;
};


#endif //SOLVR_CONSTANT_H
