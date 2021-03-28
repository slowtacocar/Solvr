//
// Created by slowt on 3/11/2021.
//

#include <sstream>
#include "Multiplication.h"
#include "Addition.h"
#include "Constant.h"
#include "Exponentiation.h"

Expression *Multiplication::simplify() const {
    Expression *combined = nullptr;
    if (getOperand1().symbol() == '+' && getOperand2().symbol() != '+') {
        std::vector<Expression *> terms = ((Addition &) getOperand1()).getTerms();
        for (auto term : terms) {
            if (combined) {
                combined = new Addition(combined, new Multiplication(term->copy(), getOperand2().copy()));
            } else {
                combined = new Multiplication(term->copy(), getOperand2().copy());
            }
        }
        Expression *ret = combined->simplify();
        delete combined;
        return ret;
    }
    if (getOperand2().symbol() == '+' && getOperand1().symbol() != '+') {
        std::vector<Expression *> terms = ((Addition &) getOperand2()).getTerms();
        for (auto term : terms) {
            if (combined) {
                combined = new Addition(combined, new Multiplication(term->copy(), getOperand1().copy()));
            } else {
                combined = new Multiplication(term->copy(), getOperand1().copy());
            }
        }
        Expression *ret = combined->simplify();
        delete combined;
        return ret;
    }
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
            double cons = ((Constant &) ((Exponentiation *) power)->getOperand2()).getValue();
            variables.emplace_back(cons, &((Exponentiation *) power)->getOperand1());
        }
        found:;
    }
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
    bool l = getOperand2().symbol() == '0' && ((Constant &) getOperand2()).getValue() == -1;
    bool f = getOperand1().symbol() == '0' && ((Constant &) getOperand1()).getValue() == -1;
    if ((f && !l) || (!f && l)) os << "-";
    if (!f) {
        if (getOperand1().symbol() == '+') os << "(" << getOperand1().toString() << ")";
        else os << getOperand1().toString();
    }
    if (!f && !l) os << "*";
    if (!l) {
        if (getOperand2().symbol() == '+') os << "(" << getOperand2().toString() << ")";
        else os << getOperand2().toString();
    }
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
    Expression *simplified1 = getOperand1().simplify();
    Expression *simplified2 = getOperand2().simplify();
    if (simplified1->symbol() == '*') {
        std::vector<Expression *> powers = ((Multiplication *) simplified1)->getPowers();
        ret.insert(ret.end(), powers.begin(), powers.end());
    } else {
        char s = simplified1->symbol();
        if ((s == '^' && ((Exponentiation *) simplified1)->getOperand2().symbol() == '0') || s == '0') {
            ret.push_back(simplified1->copy());
        } else {
            ret.push_back(new Exponentiation(simplified1->copy(), new Constant(1)));
        }
    }
    if (simplified2->symbol() == '*') {
        std::vector<Expression *> powers = ((Multiplication *) simplified2)->getPowers();
        ret.insert(ret.end(), powers.begin(), powers.end());
    } else {
        char s = simplified2->symbol();
        if ((s == '^' && ((Exponentiation *) simplified2)->getOperand2().symbol() == '0') || s == '0') {
            ret.push_back(simplified2->copy());
        } else {
            ret.push_back(new Exponentiation(simplified2->copy(), new Constant(1)));
        }
    }
    delete simplified1;
    delete simplified2;
    return ret;
}

bool Multiplication::isEqual(Expression &expression) const {
    if (expression.symbol() == '*') {
        Expression &op1 = ((Multiplication &) expression).getOperand1();
        Expression &op2 = ((Multiplication &) expression).getOperand2();
        if (op1.isEqual(getOperand1()) && op2.isEqual(getOperand2())) {
            return true;
        }
        if (op1.isEqual(getOperand2()) && op2.isEqual(getOperand1())) {
            return true;
        }
    }
    return false;
}
