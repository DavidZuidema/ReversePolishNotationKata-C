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

char pop(char *stack, int i)
{
    char value = stack[i];
    stack[i] = '\0';
    return value;
}

int isEmpty(int arrayIndex)
{
    return arrayIndex == 0;
}

typedef enum { OPERAND, OPERATOR } SymbolType;

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    int inIndex = 0, outIndex = 0, operatorsIndex = 0;
    char current, operator;
    char operators[length / 2];
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
            if ('(' == current) {
                operators[operatorsIndex++] = '(';
                continue;
            }

            if (!isValidOperand(current))
                return RPN_PARSE_ERROR_INVALID_OPERAND;

            out[outIndex++] = current;
            expecting = OPERATOR;
        }
        else if (expecting == OPERATOR)
        {
            if (')' == current) {
                while (!isEmpty(operatorsIndex) && (operator = pop(operators, --operatorsIndex)) != '(')
                    out[outIndex++] = operator;
                continue;
            }

            if (!isValidOperator(current))
                return RPN_PARSE_ERROR_INVALID_OPERATOR;

            while (!isEmpty(operatorsIndex) && precedenceOf(current) < precedenceOf(operators[operatorsIndex-1]))
                out[outIndex++] = pop(operators, --operatorsIndex);

            operators[operatorsIndex++] = current;

            expecting = OPERAND;
        }
    }

    while (operatorsIndex >= 0 && outIndex < length)
        out[outIndex++] = pop(operators, --operatorsIndex);

    return RPN_SUCCESS;
}
