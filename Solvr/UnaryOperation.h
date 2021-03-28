//
// Created by bobby on 3/27/2021.
//

#ifndef SOLVR_UNARYOPERATION_H
#define SOLVR_UNARYOPERATION_H


#include <vector>
#include "Expression.h"

class UnaryOperation : public Expression {
private:
    Expression *operand;

public:
    explicit UnaryOperation(Expression *operand);

    ~UnaryOperation() override;

    Expression &getOperand() const;

    Expression *getConstant() override;

    Expression *getNonConstant() override;

    std::vector<Expression *> allVariables() override;

    bool contains(Expression &expression) const override;
};


#endif //SOLVR_UNARYOPERATION_H
