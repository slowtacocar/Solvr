//
// Created by slowt on 3/11/2021.
//

#include "Multiplication.h"

Expression *Multiplication::simplify() {
    Expression *simplified1 = getOperand1().simplify();
    Expression *simplified2 = getOperand2().simplify();
    Expression *ret;
    if (simplified1->symbol() == '0' && simplified2->symbol() == '0') {
        ret = new Constant(((Constant *) simplified1)->getValue() * ((Constant *) simplified2)->getValue());
    }
    else if (simplified1->symbol() == '0' && simplified2->symbol() == '*' && simplified2->getConstant()) {
        double constant = ((Constant *) simplified1)->getValue() * ((Constant *) simplified2->getConstant())->getValue();
        if (constant == 0) ret = new Constant();
        else if (constant != 1) ret = new Multiplication(new Constant(constant), simplified2->getNonConstant()->copy());
        else ret = simplified2->getNonConstant()->copy();
    }
    else if (simplified1->symbol() == '*' && simplified1->getConstant() && simplified2->symbol() == '0') {
        double constant = ((Constant *) simplified1->getConstant())->getValue() * ((Constant *) simplified2)->getValue();
        if (constant == 0) ret = new Constant();
        else if (constant != 1) ret = new Multiplication(new Constant(constant), simplified1->getNonConstant()->copy());
        else ret = simplified1->getNonConstant();
    }
    else if (simplified1->symbol() == '*' && simplified1->getConstant() && simplified2->symbol() == '*' && simplified2->getConstant()) {
        double constant = ((Constant *) simplified1->getConstant())->getValue() * ((Constant *) simplified2->getConstant())->getValue();
        if (constant == 0) ret = new Constant();
        else if (constant != 1) ret = new Multiplication(new Constant(constant), Multiplication(simplified1->getNonConstant()->copy(), simplified2->getNonConstant()->copy()).simplify());
        else ret = Multiplication(simplified1->getNonConstant()->copy(), simplified2->getNonConstant()->copy()).simplify();
    }
    else ret = new Multiplication(simplified1->copy(), simplified2->copy());
    delete simplified1;
    delete simplified2;
    return ret;
}

std::string Multiplication::toString() {
    std::ostringstream os;
    if (getOperand1().symbol() == '+') os << "(" << getOperand1().toString() << ")";
    else os << getOperand1().toString();
    os << "*";
    if (getOperand2().symbol() == '+') os << "(" << getOperand2().toString() << ")";
    else os << getOperand2().toString();
    return os.str();
}

char Multiplication::symbol() {
    return '*';
}

Expression *Multiplication::copy() {
    return new Multiplication(getOperand1().copy(), getOperand2().copy());
}
