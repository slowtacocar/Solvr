//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_OPERATION_H
#define SOLVR_OPERATION_H


#include "Expression.h"

#include <vector>

class Operation : public Expression {
private:
    Expression *operand1;
    Expression *operand2;

public:
    Operation(Expression *operand1, Expression *operand2);

    Expression *getOperand1();

    Expression *getOperand2();

    Expression *getConstant() override;

    Expression *getNonConstant() override;
};


#endif //SOLVR_OPERATION_H
