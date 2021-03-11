//
// Created by slowt on 3/11/2021.
//

#include "Variable.h"

Variable::Variable(char letter) {
    this->letter = letter;
}

std::string Variable::toString() {
    return std::string(1, letter);
}

char Variable::symbol() {
    return 'a';
}

Expression *Variable::getConstant() {
    return nullptr;
}

Expression *Variable::getNonConstant() {
    return this;
}
