//
// Created by slowt on 3/11/2021.
//

#include "Exponentiation.h"

Expression *Exponentiation::simplify() const {
    Expression *simplified1 = getOperand1().simplify();
    Expression *simplified2 = getOperand2().simplify();
    Expression *ret;
    if (simplified1->symbol() == '0' && simplified2->symbol() == '0') {
        ret = new Constant(pow(((Constant *) simplified1)->getValue(), ((Constant *) simplified2)->getValue()));
    }
    else if (simplified1->symbol() == '0' && ((Constant *) simplified1)->getValue() == 0) ret = new Constant();
    else if ((simplified1->symbol() == '0' && ((Constant *) simplified1)->getValue() == 1) || (simplified2->symbol() == '0' && ((Constant *) simplified2)->getValue() == 0)) ret = new Constant(1);
    else if (simplified2->symbol() == '0' && ((Constant *) simplified2)->getValue() == 1) ret = simplified1->copy();
    else if (simplified1->symbol() == '^') {
        ret = new Exponentiation(((Exponentiation *) simplified1)->getOperand1().copy(), Multiplication(((Exponentiation *) simplified1)->getOperand2().copy(), simplified2->copy()).simplify());
    }
    else ret = new Exponentiation(simplified1->copy(), simplified2->copy());
    delete simplified1;
    delete simplified2;
    return ret;
}

std::string Exponentiation::toString() const {
    std::ostringstream os;
    if (getOperand1().symbol() == '+' || getOperand1().symbol() == '*' || getOperand1().symbol() == '^') os << "(" << getOperand1().toString() << ")";
    else os << getOperand1().toString();
    os << "^";
    if (getOperand2().symbol() == '+' || getOperand2().symbol() == '*') os << "(" << getOperand2().toString() << ")";
    else os << getOperand2().toString();
    return os.str();
}

char Exponentiation::symbol() const {
    return '^';
}

Expression *Exponentiation::copy() const {
    return new Exponentiation(getOperand1().copy(), getOperand2().copy());
}

bool Exponentiation::isEqual(Expression &expression) const {
    return expression.symbol() == '^' && ((Exponentiation &) expression).getOperand1().isEqual(getOperand1()) && ((Exponentiation &) expression).getOperand2().isEqual(getOperand2());
}
