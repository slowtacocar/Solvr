//
// Created by bobby on 3/20/2021.
//

#ifndef SOLVR_EQUATION_H
#define SOLVR_EQUATION_H


#include <vector>
#include <string>
#include "Expression.h"
#include "Variable.h"

class Equation {
private:
    Expression *side1;
    Expression *side2;

public:
    Equation(Expression *side1, Expression *side2);

    Equation(const Equation &other);

    std::vector<Equation> solve() const;

    Equation solve(Variable variable) const;

    std::string toString() const;

    std::vector<Expression *> allVariables() const;

    ~Equation();
};


#endif //SOLVR_EQUATION_H
