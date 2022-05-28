#include "calculator.h"
#include <stdint.h>
bool Calculator::isOperand(char c) { return (c >= '0' && c <= '9'); }

// utility function to find value of and operand
int Calculator::value(char c) { return (c - '0'); }

// This function evaluates simple expressions. It returns -1 if the
// given expression is invalid.
int Calculator::evaluate(char* exp)
{
    // Base Case: Given expression is empty
    if (*exp == '\0')  return -4;

    // The first character must be an operand, find its value
    int res = value(exp[0]);

    // Traverse the remaining characters in pairs
    for (int i = 1; exp[i]; i += 2)
    {
        // The next character must be an operator, and
        // next to next an operand
        char opr = exp[i], opd = exp[i + 1];

        // If next to next character is not an operand
        //if (!isOperand(opd))  return -3;

        // Update result according to the operator
        if (opr == '+')       res += value(opd);
        else if (opr == '-')  res -= value(opd);
        else if (opr == '*')  res *= value(opd);
        else if (opr == '/')  res /= value(opd);

        // If not a valid operator
        else                  return -2;
    }
    return res;
}
