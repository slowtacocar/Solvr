//
// Created by bobby on 3/20/2021.
//

#include "Equation.h"
#include "Unsolvable.h"
#include "Multiplication.h"
#include "Constant.h"
#include "Addition.h"
#include "Exponentiation.h"
#include "Logarithm.h"

Equation::Equation(const Expression *side1, const Expression *side2) {
    this->side1 = side1;
    this->side2 = side2;
}

std::vector<Equation> Equation::solve() const {
    std::vector<Equation> ret;
    for (auto var : allVariables()) {
        try {
            ret.push_back(solve(*(Variable *) var));
        } catch (Unsolvable &) {}
    }
    return ret;
}

Equation Equation::solve(const Variable& variable) const {
    auto *subtract = new Multiplication(new Constant(-1), side2->copy());
    const Expression *left = Addition(side1->copy(), subtract).simplify();
    const Expression *right = new Constant(0);
    while (true) {
        if (left->symbol() == '+') {
            const Expression &op1 = ((Addition *) left)->getOperand1();
            const Expression &op2 = ((Addition *) left)->getOperand2();
            if (op1.contains(variable) && op2.contains(variable)) {
                throw Unsolvable();
            } else if (op1.contains(variable)) {
                right = new Addition(right, new Multiplication(new Constant(-1), &op2));
                left = &op1;
            } else if (op2.contains(variable)) {
                right = new Addition(right, new Multiplication(new Constant(-1), &op1));
                left = &op2;
            }
        } else if (left->symbol() == '*') {
            const Expression &op1 = ((Multiplication *) left)->getOperand1();
            const Expression &op2 = ((Multiplication *) left)->getOperand2();
            if (op1.contains(variable) && op2.contains(variable)) {
                throw Unsolvable();
            } else if (op1.contains(variable)) {
                right = new Multiplication(right, new Exponentiation(&op2, new Constant(-1)));
                left = &op1;
            } else if (op2.contains(variable)) {
                right = new Multiplication(right, new Exponentiation(&op1, new Constant(-1)));
                left = &op2;
            }
        } else if (left->symbol() == '^') {
            const Expression &op1 = ((Exponentiation *) left)->getOperand1();
            const Expression &op2 = ((Exponentiation *) left)->getOperand2();
            if (op1.contains(variable) && op2.contains(variable)) {
                throw Unsolvable();
            } else if (op1.contains(variable)) {
                right = new Exponentiation(right, new Exponentiation(&op2, new Constant(-1)));
                left = &op1;
            } else if (op2.contains(variable)) {
                auto *cob = new Exponentiation(new Logarithm(&op1), new Constant(-1));
                right = new Multiplication(new Logarithm(right), cob);
                left = &op2;
            }
        } else {
            break;
        }
    }
    Equation ret = Equation(left, right->simplify());
    delete right;
    return ret;
}

std::string Equation::toString() const {
    return side1->toString() + "=" + side2->toString();
}

Equation::~Equation() {
    delete side1;
    delete side2;
}

Equation::Equation(const Equation &other) {
    side1 = other.side1->copy();
    side2 = other.side2->copy();
}

std::vector<const Expression *> Equation::allVariables() const {
    std::vector<const Expression *> ret = side1->allVariables();
    std::vector<const Expression *> vs2 = side2->allVariables();
    for (auto var : vs2) {
        for (auto retVar : ret) {
            if (var->isEqual(*retVar)) goto found;
        }
        ret.push_back(var);
        found:;
    }
    return ret;
}
