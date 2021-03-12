//
// Created by slowt on 3/11/2021.
//

#include "Constant.h"

Constant::Constant() {
    value = 0;
}

Constant::Constant(double value) {
    this->value = value;
}

std::string Constant::toString() const {
    std::ostringstream ss;
    ss << value;
    if (value >= 0) return ss.str();
    return "(" + ss.str() + ")";
}

double Constant::getValue() const {
    return value;
}

char Constant::symbol() const {
    return '0';
}

Expression *Constant::getConstant() {
    return this;
}

Expression *Constant::getNonConstant() {
    return nullptr;
}

Expression *Constant::copy() const {
    return new Constant(getValue());
}

bool Constant::isEqual(Expression &expression) const {
    return expression.symbol() == '0' && ((Constant &) expression).getValue() == getValue();
}
