//
// Created by slowt on 3/11/2021.
//

#ifndef SOLVR_ADDITION_H
#define SOLVR_ADDITION_H


#include "Operation.h"
#include "Constant.h"

class Addition : public Operation {
public:
    using Operation::Operation;

    Expression *simplify() override;

    std::string toString() override;

    char symbol() override;
};


#endif //SOLVR_ADDITION_H
