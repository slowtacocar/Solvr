//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_EXPRESSION_H
#define SOLVR_EXPRESSION_H


#include <string>

class Expression {
public:
    virtual Expression *simplify();

    virtual std::string toString() = 0;

    virtual char symbol() = 0;

    virtual Expression *getConstant() = 0;

    virtual Expression *getNonConstant() = 0;
};


#endif //SOLVR_EXPRESSION_H
