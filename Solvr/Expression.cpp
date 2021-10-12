//
// Created by slowt on 3/11/2021.
//

#include "Expression.h"

Expression *Expression::simplify() const {
    return copy();
}

const Expression *Expression::findCoefficient(const Expression *variable) const {
    return nullptr;
}
