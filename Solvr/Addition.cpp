//
// Created by slowt on 3/11/2021.
//

#include "Addition.h"

Expression *Addition::simplify() {
    Expression *simplified1 = getOperand1().simplify();
    Expression *simplified2 = getOperand2().simplify();
    Expression *ret;
    if (simplified1->symbol() == '0' && simplified2->symbol() == '0') {
        ret = new Constant(((Constant *) simplified1)->getValue() + ((Constant *) simplified2)->getValue());
    } else if (simplified1->symbol() == '0' && simplified2->symbol() == '+' && simplified2->getConstant()) {
        double constant = ((Constant *) simplified1)->getValue() + ((Constant *) simplified2->getConstant())->getValue();
        if (constant != 0) ret = new Addition(simplified2->getNonConstant()->copy(), new Constant(constant));
        else ret = simplified2->getNonConstant()->copy();
    } else if (simplified1->symbol() == '+' && simplified1->getConstant() && simplified2->symbol() == '0') {
        double constant = ((Constant *) simplified1->getConstant())->getValue() + ((Constant *) simplified2)->getValue();
        if (constant != 0) ret = new Addition(simplified1->getNonConstant()->copy(), new Constant(constant));
        else ret = simplified1->getNonConstant()->copy();
    } else if (simplified1->symbol() == '+' && simplified1->getConstant() && simplified2->symbol() == '+' && simplified2->getConstant()) {
        double constant = ((Constant *) simplified1->getConstant())->getValue() + ((Constant *) simplified2->getConstant())->getValue();
        if (constant != 0) ret = new Addition(Addition(simplified1->getNonConstant()->copy(), simplified2->getNonConstant()->copy()).simplify(), new Constant(constant));
        else ret = Addition(simplified1->getNonConstant()->copy(), simplified2->getNonConstant()->copy()).simplify();
    } else ret = new Addition(simplified1->copy(), simplified2->copy());
    delete simplified1;
    delete simplified2;
    return ret;
}

std::string Addition::toString() {
    return getOperand1().toString() + "+" + getOperand2().toString();
}

char Addition::symbol() {
    return '+';
}

Expression *Addition::copy() {
    return new Addition(getOperand1().copy(), getOperand2().copy());
}
