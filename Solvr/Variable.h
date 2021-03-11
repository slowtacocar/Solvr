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

    std::string toString() override;

    char symbol() override;

    Expression *getConstant() override;

    Expression *getNonConstant() override;
};


#endif //SOLVR_VARIABLE_H
