//
// Created by slowt on 3/11/2021.
//

#include "Multiplication.h"

Expression *Multiplication::simplify() const {
    Expression *simplified1 = getOperand1().simplify();
    Expression *simplified2 = getOperand2().simplify();

    std::vector<Expression *> powers = getPowers();
    std::vector<std::pair<double, Expression *>> variables;
    double constant = 1;
    for (auto power : powers) {
        if (power->symbol() == '0') constant *= ((Constant *) power)->getValue();
        else {
            for (auto &variable : variables) {
                if (variable.second->isEqual(((Exponentiation *) power)->getOperand1())) {
                    variable.first += ((Constant &) ((Exponentiation *) power)->getOperand2()).getValue();
                    goto found;
                }
            }
            variables.emplace_back(((Constant &) ((Exponentiation *) power)->getOperand2()).getValue(), &((Exponentiation *) power)->getOperand1());
            found:;
        }
    }
    Expression *combined = nullptr;
    for (auto variable : variables) {
        if (combined) {
            combined = new Multiplication(combined, Exponentiation(variable.second->copy(), new Constant(variable.first)).simplify());
        } else {
            combined = Exponentiation(variable.second->copy(), new Constant(variable.first)).simplify();
        }
    }
    if (constant == 0) return new Constant();
    if (!combined) return new Constant(constant);
    if (constant != 1) combined = new Multiplication(new Constant(constant), combined);
    delete simplified1;
    delete simplified2;
    return combined;
}

std::string Multiplication::toString() const {
    std::ostringstream os;
    if (getOperand1().symbol() == '+') os << "(" << getOperand1().toString() << ")";
    else os << getOperand1().toString();
    os << "*";
    if (getOperand2().symbol() == '+') os << "(" << getOperand2().toString() << ")";
    else os << getOperand2().toString();
    return os.str();
}

char Multiplication::symbol() const {
    return '*';
}

Expression *Multiplication::copy() const {
    return new Multiplication(getOperand1().copy(), getOperand2().copy());
}

std::vector<Expression *> Multiplication::getPowers() const {
    std::vector<Expression *> ret;
    if (getOperand1().symbol() == '*') {
        std::vector<Expression *> powers = ((Multiplication &) getOperand1()).getPowers();
        ret.insert(ret.end(), powers.begin(), powers.end());
    } else if (getOperand1().symbol() == '^' && ((Exponentiation &) getOperand1()).getOperand2().symbol() == '0') {
        ret.push_back((Exponentiation *) &getOperand1());
    } else if (getOperand1().symbol() == '0') {
        ret.push_back(&getOperand1());
    } else {
        ret.push_back(new Exponentiation(&getOperand1(), new Constant(1)));
    }
    if (getOperand2().symbol() == '*') {
        std::vector<Expression *> powers = ((Multiplication &) getOperand2()).getPowers();
        ret.insert(ret.end(), powers.begin(), powers.end());
    } else if (getOperand2().symbol() == '^' && ((Exponentiation &) getOperand2()).getOperand2().symbol() == '0') {
        ret.push_back((Exponentiation *) &getOperand2());
    } else if (getOperand2().symbol() == '0') {
        ret.push_back(&getOperand2());
    } else {
        ret.push_back(new Exponentiation(&getOperand2(), new Constant(1)));
    }
    return ret;
}

bool Multiplication::isEqual(Expression &expression) const {
    return expression.symbol() == '*' && ((((Multiplication &) expression).getOperand1().isEqual(getOperand1()) && ((Multiplication &) expression).getOperand2().isEqual(getOperand2())) || (((Multiplication &) expression).getOperand1().isEqual(getOperand2()) && ((Multiplication &) expression).getOperand2().isEqual(getOperand1())));
}
