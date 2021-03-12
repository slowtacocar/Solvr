#include "Solvr.h"

bool debug = false;

Constant *readDigits(std::string string, size_t start, size_t stop) {
    if (start == stop) throw std::invalid_argument("An empty string is not a valid number");
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
        else throw std::invalid_argument(string + " is not a valid number");
    }
    if (string[start] == '-') constant *= -1;
    if (debug) std::cout << "Parsed \"" << string.substr(start, stop - start) << "\" as " << constant << std::endl;
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
        if (debug) std::cout << "Parsed " << string[start] << " as a variable" << std::endl;
        // The expression is 1 character long and it's alphabetic (it's a variable)
        return new Variable(string[start]);
    }
    try {
        return readDigits(string, start, stop);
    }
    catch (std::invalid_argument &e) {
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
            if (debug) std::cout << "Evaluating addition at position " << lastAdd << ": " << string.substr(start, stop - start) << std::endl;
            // Addition and subtraction take precedence
            if (string[lastAdd] == '+') return new Addition(parseExpression(string, start, lastAdd), parseExpression(string, lastAdd + 1, stop));
            return new Addition(parseExpression(string, start, lastAdd), new Multiplication(new Constant(-1), parseExpression(string, lastAdd + 1, stop)));
        }
        if (lastMult > 0) {
            if (debug) std::cout << "Evaluating multiplication at position " << lastMult << ": " << string.substr(start, stop - start) << std::endl;
            // Multiplication and division are next
            if (string[lastMult] == '*') return new Multiplication(parseExpression(string, start, lastMult), parseExpression(string, lastMult + 1, stop));
            return new Multiplication(parseExpression(string, start, lastMult), new Exponentiation(parseExpression(string, lastMult + 1, stop), new Constant(-1)));
        }
        if (lastExp > 0) {
            if (debug) std::cout << "Evaluating exponentiation at position " << lastExp << ": " << string.substr(start, stop - start) << std::endl;
            // Exponentiation is the last
            return new Exponentiation(parseExpression(string, start, lastExp), parseExpression(string, lastExp + 1, stop));
        }
        // If no operators were found, throw an error
        throw std::invalid_argument(string + " is not a valid expression");
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
                Expression *exp = parseExpression(input, 0, input.length());
                if (debug) std::cout << exp->toString() << "=";
                Expression *result = exp->simplify();
                std::cout << result->toString() << std::endl;
                delete exp;
                delete result;
            }
            catch (std::invalid_argument &e) {
                std::cout << e.what() << std::endl;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
