//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_VARIABLE_H
#define SOLVR_VARIABLE_H


#include <string>
#include <vector>
#include "Expression.h"

class Variable : public Expression {
private:
    char letter;

public:
    explicit Variable(char letter);

    std::string toString() const override;

    char getLetter() const;

    char symbol() const override;

    const Expression *getConstant() const override;

    const Expression *getNonConstant() const override;

    Expression *copy() const override;

    bool isEqual(const Expression &expression) const override;

    std::vector<const Expression *> allVariables() const override;

    bool contains(const Expression &expression) const override;

    const Expression * findCoefficient(const Expression *variable) const override;
};


#endif //SOLVR_VARIABLE_H
