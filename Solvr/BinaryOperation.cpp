//
// Created by slowt on 3/11/2021.
//

#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(Expression *operand1, Expression *operand2) {
    this->operand1 = operand1;
    this->operand2 = operand2;
}

Expression &BinaryOperation::getOperand1() const {
    return *operand1;
}

Expression &BinaryOperation::getOperand2() const {
    return *operand2;
}

Expression *BinaryOperation::getConstant() {
    if (operand1->symbol() == '0') return operand1;
    if (operand2->symbol() == '0') return operand2;
    return nullptr;
}

Expression *BinaryOperation::getNonConstant() {
    if (operand1->symbol() != '0' && operand2->symbol() != '0') return this;
    if (operand1->symbol() != '0') return operand1;
    if (operand2->symbol() != '0') return operand2;
    return nullptr;
}

BinaryOperation::~BinaryOperation() {
    delete operand1;
    delete operand2;
}

bool BinaryOperation::contains(Expression &expression) const {
    return operand1->contains(expression) || operand2->contains(expression);
}

std::vector<Expression *> BinaryOperation::allVariables() {
    std::vector<Expression *> ret = operand1->allVariables();
    std::vector<Expression *> vs2 = operand2->allVariables();
    for (auto var : vs2) {
        for (auto retVar : ret) {
            if (var->isEqual(*retVar)) goto found;
        }
        ret.push_back(var);
        found:;
    }
    return ret;
}
