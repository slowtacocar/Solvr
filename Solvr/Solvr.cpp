#include "Solvr.h"

bool verbose = false;

Constant *readDigits(std::string string, size_t start, size_t stop) {
    if (start == stop) throw InvalidExpression(string.c_str());
    double constant = 0;
    double multiplier = 1;
    size_t i = start;
    if (string[start] == '-') i++;
    for (; i < stop; i++) {
        // Read the string as a number
        if (std::isdigit(string[i])) {
            if (multiplier == 1) constant *= 10;
            constant += ((double) string[i] - '0') * multiplier;
            if (multiplier < 1) multiplier /= 10;
        } else if (string[i] == '.') multiplier = 0.1;
        else throw InvalidExpression(string.c_str());
    }
    if (string[start] == '-') constant *= -1;
    if (verbose) std::cout << "Parsed \"" << string.substr(start, stop - start) << "\" as " << constant << std::endl;
    return new Constant(constant);
}

Expression *parseExpression(std::string string, size_t start, size_t stop) {
    int parens = 0;
    size_t lastAdd = 0;
    size_t lastMult = 0;
    size_t lastExp = 0;
    while (string[start] == '(' && string[stop - 1] == ')') {
        for (size_t i = start + 1; i < stop - 1; i++) {
            if (string[i] == '(') parens++;
            else if (string[i] == ')') parens--;
            if (parens < 0) goto endwhile;
        }
        start++;
        stop--;
    }
    endwhile:
    parens = 0;
    if (start + 1 == stop && std::isalpha(string[start])) {
        if (verbose) std::cout << "Parsed " << string[start] << " as a variable" << std::endl;
        // The expression is 1 character long and it's alphabetic (it's a variable)
        return new Variable(string[start]);
    }
    try {
        return readDigits(string, start, stop);
    }
    catch (InvalidExpression &) {
        for (size_t i = start; i < stop; i++) {
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
            if (verbose) {
                std::cout << "Evaluating addition at position " << lastAdd << ": ";
                std::cout << string.substr(start, stop - start) << std::endl;
            }
            // Addition and subtraction take precedence
            Expression *left = parseExpression(string, start, lastAdd);
            Expression *right = parseExpression(string, lastAdd + 1, stop);
            if (string[lastAdd] == '+') return new Addition(left, right);
            return new Addition(left, new Multiplication(new Constant(-1), right));
        }
        if (lastMult > 0) {
            if (verbose) {
                std::cout << "Evaluating multiplication at position " << lastMult << ": ";
                std::cout << string.substr(start, stop - start) << std::endl;
            }
            // Multiplication and division are next
            Expression *left = parseExpression(string, start, lastMult);
            Expression *right = parseExpression(string, lastMult + 1, stop);
            if (string[lastMult] == '*') return new Multiplication(left, right);
            return new Multiplication(left, new Exponentiation(right, new Constant(-1)));
        }
        if (lastExp > 0) {
            if (verbose) {
                std::cout << "Evaluating exponentiation at position " << lastExp << ": ";
                std::cout << string.substr(start, stop - start) << std::endl;
            }
            // Exponentiation is the last
            Expression *left = parseExpression(string, start, lastExp);
            Expression *right = parseExpression(string, lastExp + 1, stop);
            return new Exponentiation(left, right);
        }
        // If no operators were found, throw an error
        throw InvalidExpression(string.c_str());
    }
}

int main() {
    std::string input;
    bool running = true;
    std::cout << "Welcome to Solvr. Type exit to quit." << std::endl;
    while (running) {
        std::cout << ">>";
        std::cin >> input;

        if (input == "exit") {
            running = false;
        } else {
            try {
                for (size_t i = 0; i < input.length(); i++) {
                    if (input[i] == '=') {
                        Expression *side1 = parseExpression(input, 0, i);
                        Expression *side2 = parseExpression(input, i + 1, input.length());
                        Equation equ(side1, side2);
                        if (verbose) std::cout << equ.toString() << std::endl;
                        std::vector<Equation> results = equ.solve();
                        for (const auto &result : results) {
                            std::cout << result.toString() << std::endl;
                        }
                        goto end;
                    }
                }
                Expression *exp = parseExpression(input, 0, input.length());
                if (verbose) std::cout << exp->toString() << "=";
                Expression *result = exp->simplify();
                std::cout << result->toString() << std::endl;
                delete exp;
                delete result;
            }
            catch (InvalidExpression &e) {
                std::cout << e.what() << " is not a valid expression" << std::endl;
            }
            end:;
            std::cout << std::endl;
        }
    }
    return 0;
}
