//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_BINARYOPERATION_H
#define SOLVR_BINARYOPERATION_H


#include "Expression.h"

#include <vector>

class BinaryOperation : public Expression {
private:
    Expression *operand1;
    Expression *operand2;

public:
    BinaryOperation(Expression *operand1, Expression *operand2);

    ~BinaryOperation() override;

    Expression &getOperand1() const;

    Expression &getOperand2() const;

    Expression *getConstant() override;

    Expression *getNonConstant() override;

    std::vector<Expression *> allVariables() override;

    bool contains(Expression &expression) const override;
};


#endif //SOLVR_BINARYOPERATION_H
