//
// Created by slowt on 3/11/2021.
//

#include <sstream>
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
    return ss.str();
}

double Constant::getValue() const {
    return value;
}

char Constant::symbol() const {
    return '0';
}

const Expression *Constant::getConstant() const {
    return this;
}

const Expression *Constant::getNonConstant() const {
    return nullptr;
}

Expression *Constant::copy() const {
    return new Constant(getValue());
}

bool Constant::isEqual(const Expression &expression) const {
    return expression.symbol() == '0' && ((Constant &) expression).getValue() == getValue();
}

bool Constant::contains(const Expression &expression) const {
    return isEqual(expression);
}

std::vector<const Expression *> Constant::allVariables() const {
    return std::vector<const Expression *>();
}

const Expression *Constant::findCoefficient(const Expression *variable) const {
    if (variable == nullptr) return this->copy();
    return nullptr;
}
