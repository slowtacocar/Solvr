//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_BINARYOPERATION_H
#define SOLVR_BINARYOPERATION_H


#include <vector>
#include "Expression.h"

class BinaryOperation : public Expression {
private:
    const Expression *operand1;
    const Expression *operand2;

public:
    BinaryOperation(const Expression *operand1, const Expression *operand2);

    ~BinaryOperation() override;

    const Expression &getOperand1() const;

    const Expression &getOperand2() const;

    const Expression *getConstant() const override;

    const Expression *getNonConstant() const override;

    std::vector<const Expression *> allVariables() const override;

    bool contains(const Expression &expression) const override;
};


#endif //SOLVR_BINARYOPERATION_H
