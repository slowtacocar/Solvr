//
// Created by Bobby George on 10/11/21.
//

#include "System.h"
#include "Constant.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Unsolvable.h"

System::System(std::vector<Equation> &equations) {
    this->equations = equations;
}

std::vector<Equation> System::solve() const {
    std::vector<const Expression *> variables = allVariables();
    double matrix[equations.size()][variables.size() + 1];
    for (int i = 0; i < equations.size(); i++) {
        Equation equation = equations[i].simplify();
        for (int j = 0; j < variables.size(); j++) {
            const Expression *coefficient = equation.findCoefficient(variables[j]);
            if (coefficient == nullptr) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = ((Constant *) coefficient)->getValue();
                delete coefficient;
            }
        }
        const Expression *coefficient = equation.findCoefficient(nullptr);
        if (coefficient == nullptr) {
            matrix[i][variables.size()] = 0;
        } else {
            matrix[i][variables.size()] = -((Constant *) coefficient)->getValue();
            delete coefficient;
        }
    }
    for (size_t i = 0; i < equations.size() - 1; i++) {
        for (size_t j = 0; j < variables.size(); j++) {
            if (matrix[i][j] != 0) {
                for (size_t k = i + 1; k < equations.size(); k++) {
                    double c = matrix[k][j] / matrix[i][j];
                    for (size_t l = 0; l <= variables.size(); l++) {
                        matrix[k][l] -= matrix[i][l] * c;
                    }
                }
                break;
            }
        }
    }
    for (size_t i = equations.size() - 1; i > 0; i--) {
        for (size_t j = 0; j < variables.size(); j++) {
            if (matrix[i][j] != 0) {
                for (size_t k = i - 1; k < (size_t) -1; k--) {
                    double c = matrix[k][j] / matrix[i][j];
                    for (size_t l = 0; l <= variables.size(); l++) {
                        matrix[k][l] -= matrix[i][l] * c;
                    }
                }
                break;
            }
        }
    }
    std::vector<Equation> solutions;
    for (size_t i = 0; i < equations.size(); i++) {
        for (size_t j = 0; j < variables.size(); j++) {
            if (matrix[i][j] != 0) {
                double c = 1 / matrix[i][j];
                Expression *solution = new Constant(matrix[i][variables.size()]);
                for (size_t k = j + 1; k < variables.size(); k++) {
                    if (matrix[i][k] != 0) {
                        solution = new Addition(solution, new Multiplication(variables[k]->copy(), new Constant(-matrix[i][k])));
                    }
                }
                solutions.emplace_back(variables[j]->copy(),  Multiplication(new Constant(c), solution).simplify());
                goto pivot;
            }
        }
        if (matrix[i][variables.size()] != 0) {
            throw Unsolvable();
        }
        pivot:;
    }
    return solutions;
}

std::vector<const Expression *> System::allVariables() const {
    std::vector<const Expression *> variables;
    for (const auto& equation : equations) {
        std::vector<const Expression *> equationVariables = equation.allVariables();
        for (auto equationVariable : equationVariables) {
            for (auto variable : variables) {
                if (equationVariable->isEqual(*variable)) goto found;
            }
            variables.push_back(equationVariable);
            found:;
        }
    }
    return variables;
}

