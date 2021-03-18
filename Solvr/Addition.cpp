//
// Created by slowt on 3/11/2021.
//

#include "Addition.h"

Expression *Addition::simplify() const {
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
        Expression *m = Multiplication(new Constant(variable.first), variable.second->copy()).simplify();
        if (m->symbol() == '0') {
            constant += ((Constant *) m)->getValue();
            delete m;
        } else {
            if (combined) {
                combined = new Addition(combined, m);
            } else {
                combined = m;
            }
        }
    }
    if (!combined) return new Constant(constant);
    if (constant != 0) combined = new Addition(combined, new Constant(constant));
    terms.clear();
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
    } else {
        Expression *simplified1 = getOperand1().simplify();
        if ((simplified1->symbol() == '*' && simplified1->getConstant()) || simplified1->symbol() == '0') {
            ret.push_back(simplified1->copy());
        } else {
            ret.push_back(new Multiplication(new Constant(1), simplified1->copy()));
        }
        delete simplified1;
    }
    if (getOperand2().symbol() == '+') {
        std::vector<Expression *> terms = ((Addition &) getOperand2()).getTerms();
        ret.insert(ret.end(), terms.begin(), terms.end());
    } else {
        Expression *simplified2 = getOperand2().simplify();
        if ((simplified2->symbol() == '*' && simplified2->getConstant()) || simplified2->symbol() == '0') {
            ret.push_back(simplified2->copy());
        } else {
            ret.push_back(new Multiplication(new Constant(1), simplified2->copy()));
        }
        delete simplified2;
    }
    return ret;
}

bool Addition::isEqual(Expression &expression) const {
    return expression.symbol() == '+' && ((((Addition &) expression).getOperand1().isEqual(getOperand1()) && ((Addition &) expression).getOperand2().isEqual(getOperand2())) || (((Addition &) expression).getOperand1().isEqual(getOperand2()) && ((Addition &) expression).getOperand2().isEqual(getOperand1())));
}
