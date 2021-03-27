//
// Created by bobby on 3/27/2021.
//

#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(Expression *operand) {
    this->operand = operand;
}

Expression &UnaryOperation::getOperand() const {
    return *operand;
}

Expression *UnaryOperation::getConstant() {
    if (operand->symbol() == '0') return operand;
    return nullptr;
}

Expression *UnaryOperation::getNonConstant() {
    if (operand->symbol() != '0') return operand;
    return nullptr;
}

UnaryOperation::~UnaryOperation() {
    delete operand;
}

bool UnaryOperation::contains(Expression &expression) const {
    return operand->contains(expression);
}

std::vector<Expression *> UnaryOperation::allVariables() {
    return operand->allVariables();
}
