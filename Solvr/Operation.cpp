//
// Created by slowt on 3/11/2021.
//

#include "Operation.h"

Operation::Operation(Expression *operand1, Expression *operand2) {
    this->operand1 = operand1;
    this->operand2 = operand2;
}

Expression &Operation::getOperand1() const {
    return *operand1;
}

Expression &Operation::getOperand2() const {
    return *operand2;
}

Expression *Operation::getConstant() {
    if (operand1->symbol() == '0') return operand1;
    if (operand2->symbol() == '0') return operand2;
    return nullptr;
}

Expression *Operation::getNonConstant() {
    if (operand1->symbol() != '0' && operand2->symbol() != '0') return this;
    if (operand1->symbol() != '0') return operand1;
    if (operand2->symbol() != '0') return operand2;
    return nullptr;
}

Operation::~Operation() {
    delete operand1;
    delete operand2;
}
