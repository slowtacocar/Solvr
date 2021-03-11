//
// Created by slowt on 3/11/2021.
//

#include "Addition.h"

Expression *Addition::simplify() {
    Expression *simplified1 = getOperand1()->simplify();
    Expression *simplified2 = getOperand2()->simplify();
    if (simplified1->symbol() == '0' && simplified2->symbol() == '0') {
        return new Constant(((Constant *) simplified1)->getValue() + ((Constant *) simplified2)->getValue());
    }
    if (simplified1->symbol() == '0' && simplified2->symbol() == '+' && simplified2->getConstant()) {
        Constant constant(((Constant *) simplified1)->getValue() + ((Constant *) simplified2->getConstant())->getValue());
        if (constant.getValue() != 0) return new Addition(simplified2->getNonConstant(), &constant);
        return simplified2->getNonConstant();
    }
    if (simplified1->symbol() == '+' && simplified1->getConstant() && simplified2->symbol() == '0') {
        Constant constant(((Constant *) simplified1->getConstant())->getValue() + ((Constant *) simplified2)->getValue());
        if (constant.getValue() != 0) return new Addition(simplified1->getNonConstant(), &constant);
        return simplified1->getNonConstant();
    }
    if (simplified1->symbol() == '+' && simplified1->getConstant() && simplified2->symbol() == '+' &&
        simplified2->getConstant()) {
        Constant constant(((Constant *) simplified1->getConstant())->getValue() + ((Constant *) simplified2->getConstant())->getValue());
        if (constant.getValue() != 0) return new Addition(Addition(simplified1->getNonConstant(), simplified2->getNonConstant()).simplify(), &constant);
        return Addition(simplified1->getNonConstant(), simplified2->getNonConstant()).simplify();
    }
    return new Addition(simplified1, simplified2);
}

std::string Addition::toString() {
    return getOperand1()->toString() + "+" + getOperand2()->toString();
}

char Addition::symbol() {
    return '+';
}
