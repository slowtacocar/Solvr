//
// Created by bobby on 3/20/2021.
//

#ifndef SOLVR_INVALIDEXPRESSION_H
#define SOLVR_INVALIDEXPRESSION_H


#include <exception>

class InvalidExpression : public std::exception {
public:
    using std::exception::exception;
};


#endif //SOLVR_INVALIDEXPRESSION_H
