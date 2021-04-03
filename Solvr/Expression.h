//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_EXPRESSION_H
#define SOLVR_EXPRESSION_H


#include <string>
#include <vector>

class Expression {
public:
    virtual Expression *simplify() const;

    virtual std::string toString() const = 0;

    virtual char symbol() const = 0;

    virtual const Expression *getConstant() const = 0;

    virtual const Expression *getNonConstant() const = 0;

    virtual ~Expression() = default;

    virtual Expression *copy() const = 0;

    virtual bool isEqual(const Expression &expression) const = 0;

    virtual std::vector<const Expression *> allVariables() const = 0;

    virtual bool contains(const Expression &expression) const = 0;
};


#endif //SOLVR_EXPRESSION_H
