//
// Created by slowt on 3/11/2021.
//

#include "Addition.h"

Expression *Addition::simplify() const {
    Expression *simplified1 = getOperand1().simplify();
    Expression *simplified2 = getOperand2().simplify();

    std::vector<Expression *> terms = getTerms();
    std::vector<std::pair<double, Expression *>> variables;
    double constant = 0;
    for (auto term : terms) {
        if (term->symbol() == '0') constant += ((Constant *) term)->getValue();
        else {
            for (auto &variable : variables) {
                if (variable.second->isEqual(*term->getNonConstant())) {
                    variable.first += ((Constant *) term->getConstant())->getValue();
                    goto found;
                }
            }
            variables.emplace_back(((Constant *) term->getConstant())->getValue(), term->getNonConstant());
            found:;
        }
    }
    Expression *combined = nullptr;
    for (auto variable : variables) {
        if (combined) {
            combined = new Addition(combined, Multiplication(new Constant(variable.first), variable.second->copy()).simplify());
        } else {
            combined = Multiplication(new Constant(variable.first), variable.second->copy()).simplify();
        }
    }
    if (!combined) return new Constant(constant);
    if (constant != 0) combined = new Addition(combined, new Constant(constant));
    delete simplified1;
    delete simplified2;
    return combined;
}

std::string Addition::toString() const {
    return getOperand1().toString() + "+" + getOperand2().toString();
}

char Addition::symbol() const {
    return '+';
}

Expression *Addition::copy() const {
    return new Addition(getOperand1().copy(), getOperand2().copy());
}

std::vector<Expression *> Addition::getTerms() const {
    std::vector<Expression *> ret;
    if (getOperand1().symbol() == '+') {
        std::vector<Expression *> terms = ((Addition &) getOperand1()).getTerms();
        ret.insert(ret.end(), terms.begin(), terms.end());
    } else if (getOperand1().symbol() == '*' && getOperand1().getConstant()) {
        ret.push_back((Multiplication *) &getOperand1());
    } else if (getOperand1().symbol() == '0') {
        ret.push_back(&getOperand1());
    } else {
        ret.push_back(new Multiplication(new Constant(1), &getOperand1()));
    }
    if (getOperand2().symbol() == '+') {
        std::vector<Expression *> terms = ((Addition &) getOperand2()).getTerms();
        ret.insert(ret.end(), terms.begin(), terms.end());
    } else if (getOperand2().symbol() == '*' && getOperand2().getConstant()) {
        ret.push_back((Multiplication *) &getOperand2());
    } else if (getOperand2().symbol() == '0') {
        ret.push_back(&getOperand2());
    } else {
        ret.push_back(new Multiplication(new Constant(1), &getOperand2()));
    }
    return ret;
}

bool Addition::isEqual(Expression &expression) const {
    return expression.symbol() == '+' && ((((Addition &) expression).getOperand1().isEqual(getOperand1()) && ((Addition &) expression).getOperand2().isEqual(getOperand2())) || (((Addition &) expression).getOperand1().isEqual(getOperand2()) && ((Addition &) expression).getOperand2().isEqual(getOperand1())));
}
