//
// Created by slowt on 3/11/2021.
//

#include "Multiplication.h"

Expression *Multiplication::simplify() const {
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
        Expression *e = Exponentiation(variable.second->copy(), new Constant(variable.first)).simplify();
        if (e->symbol() == '0') {
            constant *= ((Constant *) e)->getValue();
            delete e;
        } else {
            if (combined) {
                combined = new Multiplication(combined, e);
            } else {
                combined = e;
            }
        }
    }
    if (constant == 0) {
        delete combined;
        return new Constant();
    }
    if (!combined) return new Constant(constant);
    if (constant != 1) combined = new Multiplication(new Constant(constant), combined);
    powers.clear();
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
    } else {
        Expression *simplified1 = getOperand1().simplify();
        if ((simplified1->symbol() == '^' && ((Exponentiation *) simplified1)->getOperand2().symbol() == '0') ||
            simplified1->symbol() == '0') {
            ret.push_back(simplified1->copy());
        } else {
            ret.push_back(new Exponentiation(simplified1->copy(), new Constant(1)));
        }
        delete simplified1;
    }
    if (getOperand2().symbol() == '*') {
        std::vector<Expression *> powers = ((Multiplication &) getOperand2()).getPowers();
        ret.insert(ret.end(), powers.begin(), powers.end());
    } else {
        Expression *simplified2 = getOperand2().simplify();
        if ((simplified2->symbol() == '^' && ((Exponentiation *) simplified2)->getOperand2().symbol() == '0') ||
            simplified2->symbol() == '0') {
            ret.push_back(simplified2->copy());
        } else {
            ret.push_back(new Exponentiation(simplified2->copy(), new Constant(1)));
        }
        delete simplified2;
    }
    return ret;
}

bool Multiplication::isEqual(Expression &expression) const {
    return expression.symbol() == '*' && ((((Multiplication &) expression).getOperand1().isEqual(getOperand1()) && ((Multiplication &) expression).getOperand2().isEqual(getOperand2())) || (((Multiplication &) expression).getOperand1().isEqual(getOperand2()) && ((Multiplication &) expression).getOperand2().isEqual(getOperand1())));
}
