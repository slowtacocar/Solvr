//
// Created by bobby on 3/27/2021.
//

#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(const Expression *operand) {
    this->operand = operand;
}

const Expression &UnaryOperation::getOperand() const {
    return *operand;
}

const Expression *UnaryOperation::getConstant() const {
    if (operand->symbol() == '0') return operand;
    return nullptr;
}

const Expression *UnaryOperation::getNonConstant() const {
    if (operand->symbol() != '0') return operand;
    return nullptr;
}

UnaryOperation::~UnaryOperation() {
    delete operand;
}

bool UnaryOperation::contains(const Expression &expression) const {
    return operand->contains(expression);
}

std::vector<const Expression *> UnaryOperation::allVariables() const {
    return operand->allVariables();
}
