//
// Created by Bobby George on 10/11/21.
//

#ifndef SOLVR_SYSTEM_H
#define SOLVR_SYSTEM_H


#include <vector>
#include "Equation.h"

class System {
private:
    std::vector<Equation> equations;

public:
    explicit System(std::vector<Equation> &equations);

    std::vector<Equation> solve() const;

    std::vector<const Expression *> allVariables() const;
};

#endif //SOLVR_SYSTEM_H
