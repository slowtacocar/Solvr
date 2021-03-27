//
// Created by slowt on 3/11/2021.
//

#include "Variable.h"

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

Expression *Variable::getConstant() {
    return nullptr;
}

Expression *Variable::getNonConstant() {
    return this;
}

Expression *Variable::copy() const {
    return new Variable(this->getLetter());
}

bool Variable::isEqual(Expression &expression) const {
    return expression.symbol() == 'a' && ((Variable &) expression).getLetter() == getLetter();
}

std::vector<Expression *> Variable::allVariables() {
    return std::vector<Expression *>(1, this);
}

bool Variable::contains(Expression &expression) const {
    return isEqual(expression);
}
