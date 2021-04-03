//
// Created by bobby on 3/27/2021.
//

#ifndef SOLVR_UNARYOPERATION_H
#define SOLVR_UNARYOPERATION_H


#include <vector>
#include "Expression.h"

class UnaryOperation : public Expression {
private:
    const Expression *operand;

public:
    explicit UnaryOperation(const Expression *operand);

    ~UnaryOperation() override;

    const Expression &getOperand() const;

    const Expression *getConstant() const override;

    const Expression *getNonConstant() const override;

    std::vector<const Expression *> allVariables() const override;

    bool contains(const Expression &expression) const override;
};


#endif //SOLVR_UNARYOPERATION_H
