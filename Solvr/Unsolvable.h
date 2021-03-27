//
// Created by bobby on 3/20/2021.
//

#ifndef SOLVR_UNSOLVABLE_H
#define SOLVR_UNSOLVABLE_H


#include <exception>

class Unsolvable : public std::exception {
public:
    using std::exception::exception;
};


#endif //SOLVR_UNSOLVABLE_H
