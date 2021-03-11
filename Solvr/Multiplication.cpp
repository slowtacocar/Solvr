//
// Created by slowt on 3/11/2021.
//

#include "Multiplication.h"

Expression *Multiplication::simplify() {
    Expression *simplified1 = getOperand1()->simplify();
    Expression *simplified2 = getOperand2()->simplify();
    if (simplified1->symbol() == '0' && simplified2->symbol() == '0') {
        return new Constant(((Constant *) simplified1)->getValue() * ((Constant *) simplified2)->getValue());
    }
    if (simplified1->symbol() == '0' && simplified2->symbol() == '*' && simplified2->getConstant()) {
        Constant constant(((Constant *) simplified1)->getValue() * ((Constant *) simplified2->getConstant())->getValue());
        if (constant.getValue() == 0) return new Constant();
        if (constant.getValue() != 1) return new Multiplication(&constant, simplified2->getNonConstant());
        return simplified2->getNonConstant();
    }
    if (simplified1->symbol() == '*' && simplified1->getConstant() && simplified2->symbol() == '0') {
        Constant constant(((Constant *) simplified1->getConstant())->getValue() * ((Constant *) simplified2)->getValue());
        if (constant.getValue() == 0) return new Constant();
        if (constant.getValue() != 1) return new Multiplication(&constant, simplified1->getNonConstant());
        return simplified1->getNonConstant();
    }
    if (simplified1->symbol() == '*' && simplified1->getConstant() && simplified2->symbol() == '*' &&
        simplified2->getConstant()) {
        Constant constant(((Constant *) simplified1->getConstant())->getValue() * ((Constant *) simplified2->getConstant())->getValue());
        if (constant.getValue() == 0) return new Constant();
        if (constant.getValue() != 1) return new Multiplication(&constant, Multiplication(simplified1->getNonConstant(), simplified2->getNonConstant()).simplify());
        return Multiplication(simplified1->getNonConstant(), simplified2->getNonConstant()).simplify();
    }
    return new Multiplication(simplified1, simplified2);
}

std::string Multiplication::toString() {
    std::ostringstream os;
    if (getOperand1()->symbol() == '+') os << "(" << getOperand1()->toString() << ")";
    else os << getOperand1()->toString();
    os << "*";
    if (getOperand2()->symbol() == '+') os << "(" << getOperand2()->toString() << ")";
    else os << getOperand2()->toString();
    return os.str();
}

char Multiplication::symbol() {
    return '*';
}
