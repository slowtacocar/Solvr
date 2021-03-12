//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_VARIABLE_H
#define SOLVR_VARIABLE_H


#include "Expression.h"

#include <string>

class Variable : public Expression {
private:
    char letter;

public:
    explicit Variable(char letter);

    std::string toString() const override;

    char getLetter() const;

    char symbol() const override;

    Expression *getConstant() override;

    Expression *getNonConstant() override;

    Expression* copy() const override;

    bool isEqual(Expression &expression) const override;
};


#endif //SOLVR_VARIABLE_H
