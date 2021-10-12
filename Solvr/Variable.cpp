//
// Created by slowt on 3/11/2021.
//

#include "Variable.h"
#include "Constant.h"

Variable::Variable(char letter) {
    this->letter = letter;
}

std::string Variable::toString() const {
    return std::string(1, letter);
}

char Variable::getLetter() const {
    return letter;
}

char Variable::symbol() const {
    return 'a';
}

const Expression *Variable::getConstant() const {
    return nullptr;
}

const Expression *Variable::getNonConstant() const {
    return this;
}

Expression *Variable::copy() const {
    return new Variable(this->getLetter());
}

bool Variable::isEqual(const Expression &expression) const {
    return expression.symbol() == 'a' && ((Variable &) expression).getLetter() == getLetter();
}

std::vector<const Expression *> Variable::allVariables() const {
    return std::vector<const Expression *>(1, this);
}

bool Variable::contains(const Expression &expression) const {
    return isEqual(expression);
}

const Expression *Variable::findCoefficient(const Expression *variable) const {
    if (variable == nullptr) return nullptr;
    if (isEqual(*variable)) return new Constant(1);
    return nullptr;
}
