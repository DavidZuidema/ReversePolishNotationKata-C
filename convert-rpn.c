#include <stdlib.h>
#include "convert-rpn.h"

int isValidOperator(char subject)
{
    switch (subject) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return 1;
    default:
        return 0;
    }
}

int isValidOperand(char subject)
{
    return 93 < subject && subject < 123;
}

int precedenceOf(char subject)
{
    switch (subject) {
    case '^': return 5;
    case '/': return 4;
    case '*': return 3;
    case '-': return 2;
    case '+': return 1;
    default: return 0;
    }
}

typedef enum { OPERAND, OPERATOR } SymbolType;

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    int inIndex = 0, outIndex = 0, operatorsIndex = 0;
    char current;
    char operators[length];
    SymbolType expecting = OPERAND;

    if (in == NULL || out == NULL || length < 1)
        return RPN_INVALID_ARGS;

    while (inIndex < length && outIndex < length)
    {
        current = in[inIndex++];

        if (current == '\0')
            break;

        if (expecting == OPERAND)
        {
            if (!isValidOperand(current))
                return RPN_PARSE_ERROR_INVALID_OPERAND;

            out[outIndex++] = current;
            expecting = OPERATOR;
        }
        else if (expecting == OPERATOR)
        {
            if (!isValidOperator(current))
                return RPN_PARSE_ERROR_INVALID_OPERATOR;

            while (precedenceOf(current) < precedenceOf(operators[operatorsIndex])) {
                out[outIndex++] = operators[--operatorsIndex];
                operators[operatorsIndex] = '\0';
            }
            operators[operatorsIndex++] = current;

            expecting = OPERAND;
        }
    }

    while (operatorsIndex > 0 && outIndex < length)
        out[outIndex++] = operators[--operatorsIndex];

    return RPN_SUCCESS;
}
