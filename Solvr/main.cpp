#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Expression.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Constant.h"
#include "Exponentiation.h"
#include "InvalidExpression.h"
#include "Logarithm.h"
#include "Variable.h"
#include "Equation.h"
#include "System.h"
#include "Unsolvable.h"

Expression *parseExpression(std::string string, size_t start, size_t stop) {
    int parens = 0;
    size_t lastAdd = 0;
    size_t lastMult = 0;
    size_t lastExp = 0;
    size_t i;
    for (i = start; i < stop; i++) {
        if (string[i] == '(') parens++;
        else if (string[i] == ')') parens--;
        else if (parens == 0) {
            // If the parentheses are matched, record the operator
            if (string[i] == '+' || string[i] == '-') lastAdd = i;
            else if (string[i] == '*' || string[i] == '/') lastMult = i;
            else if (lastExp == 0 && string[i] == '^') lastExp = i;
        }
    }
    if (lastAdd > 0) {
        // Addition and subtraction take precedence
        Expression *left = parseExpression(string, start, lastAdd);
        Expression *right = parseExpression(string, lastAdd + 1, stop);
        if (string[lastAdd] == '+') return new Addition(left, right);
        return new Addition(left, new Multiplication(new Constant(-1), right));
    }
    if (lastMult > 0) {
        // Multiplication and division are next
        Expression *left = parseExpression(string, start, lastMult);
        Expression *right = parseExpression(string, lastMult + 1, stop);
        if (string[lastMult] == '*') return new Multiplication(left, right);
        return new Multiplication(left, new Exponentiation(right, new Constant(-1)));
    }
    if (lastExp > 0) {
        // Exponentiation is the last
        Expression *left = parseExpression(string, start, lastExp);
        Expression *right = parseExpression(string, lastExp + 1, stop);
        return new Exponentiation(left, right);
    }
    Expression *ret = nullptr;
    i = start;
    if (string[i] == '-') {
        ret = new Constant(-1);
        i++;
    }
    if (start == stop) throw InvalidExpression();
    for (; i < stop;) {
        if (stop - i > 4 && string.substr(i, 3) == "ln(") {
            i += 2;
            int st = i;
            int p = 0;
            for (; i < stop; i++) {
                if (string[i] == '(') p++;
                if (string[i] == ')') p--;
                if (p == 0) {
                    if (ret) ret = new Multiplication(ret, new Logarithm(parseExpression(string, st + 1, i)));
                    else ret = new Logarithm(parseExpression(string, st + 1, i));
                    i++;
                    break;
                }
            }
            if (p != 0) throw InvalidExpression();
        } else if (std::isalpha(string[i])) {
            if (ret) ret = new Multiplication(ret, new Variable(string[i]));
            else ret = new Variable(string[i]);
            i++;
        } else if (std::isdigit(string[i])) {
            double constant = 0;
            double multiplier = 1;
            for (; i < stop; i++) {
                // Read the string as a number
                if (std::isdigit(string[i])) {
                    if (multiplier == 1) constant *= 10;
                    constant += ((double) string[i] - '0') * multiplier;
                    if (multiplier < 1) multiplier /= 10;
                } else if (string[i] == '.') multiplier = 0.1;
                else break;
            }
            if (ret) ret = new Multiplication(ret, new Constant(constant));
            else ret = new Constant(constant);
        } else if (string[i] == '(') {
            int st = i;
            int p = 0;
            for (; i < stop; i++) {
                if (string[i] == '(') p++;
                if (string[i] == ')') p--;
                if (p == 0) {
                    if (ret) ret = new Multiplication(ret, parseExpression(string, st + 1, i));
                    else ret = parseExpression(string, st + 1, i);
                    i++;
                    break;
                }
            }
            if (p != 0) throw InvalidExpression();
        } else {
            throw InvalidExpression();
        }
    }
    return ret;
}

std::string getInput(std::string input) {
    std::ostringstream os;
    try {
        size_t start = 0;
        Expression *side1 = nullptr;
        std::vector<Equation> equations;
        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] == '=') {
                side1 = parseExpression(input, start, i);
                start = i + 1;
            } else if (input[i] == ',') {
                Expression *side2 = parseExpression(input, start, i);
                equations.emplace_back(side1, side2);
                start = i + 1;
            }
        }
        Expression *side2 = parseExpression(input, start, input.length());
        if (side1 == nullptr) {
            Expression *result = side2->simplify();
            os << result->toString() << std::endl;
            delete side2;
            delete result;
        } else {
            Equation equ(side1, side2);
            if (equations.empty()) {
                std::vector<Equation> results = equ.solve();
                for (const auto &result : results) {
                    os << result.toString() << std::endl;
                }
            } else {
                equations.push_back(equ);
                System system(equations);
                try {
                    std::vector<Equation> results = system.solve();
                    for (const auto &result : results) {
                        os << result.toString() << std::endl;
                    }
                } catch (Unsolvable &) {
                    os << "No solutions" << std::endl;
                }
            }
        }

    }
    catch (InvalidExpression &) {
        os << input << " is not a valid input" << std::endl;
    }
    return os.str();
}

void runSolvr() {
    std::string input;
    bool running = true;
    std::cout << "Welcome to Solvr. Type exit to quit." << std::endl;
    while (running) {
        std::cout << ">>";
        std::cin >> input;

        if (input == "exit") {
            running = false;
        } else {
            std::cout << getInput(input) << std::endl;
        }
    }
}

void test() {
    std::string input;
    std::string yn;
    std::fstream tests;
    tests.open ("../../tests.txt", std::fstream::in | std::fstream::app);
    bool running = true;
    std::string line;
    while (getline(tests, line)) {
        for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '\t') {
                std::string in = line.substr(0, i);
                std::string res = getInput(in);
                std::ostringstream rs;
                std::string expected = line.substr(i + 1, line.length() - i - 1);
                for (size_t j = 0; j < res.length(); j++) {
                    if (res[j] == '\n') {
                        rs << "\\n";
                    } else if (j + 1 < res.length() && res[j] == '\r' && res[j + 1] == '\n') {
                        rs << "\\n";
                        j++;
                    } else {
                        rs << res[j];
                    }
                }
                std::string rsstr = rs.str();
                if (rsstr != expected) {
                    std::cout << "Test failed: " << in << std::endl;
                    std::cout << "Expected " << expected << " but got " << rsstr << std::endl;
                    goto fail;
                }
                break;
            }
        }
    }
    tests.clear();
    std::cout << "Welcome to Solvr. Type exit to quit." << std::endl;
    std::cout << "Solvr is in test mode. Inputs will be saved to a test suite." << std::endl;
    while (running) {
        std::cout << ">>";
        std::cin >> input;

        if (input == "exit") {
            running = false;
        } else {
            std::string out = getInput(input);
            std::cout << out;
            std::cout << "Is this correct? ";
            std::cin >> yn;
            std::cout << std::endl;
            if (yn == "y") {
                tests << input << "\t";
                for (size_t i = 0; i < out.length(); i++) {
                    if (out[i] == '\n') {
                        tests << "\\n";
                    } else if (i + 1 < out.length() && out[i] == '\r' && out[i + 1] == '\n') {
                        tests << "\\n";
                        i++;
                    } else {
                        tests << out[i];
                    }
                }
                tests << std::endl;
            }
        }
    }
    fail:
    tests.close();
}

int main() {
    test();
    return 0;
}
