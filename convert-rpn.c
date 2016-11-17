#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "convert-rpn.h"

int isValidOperator(char subject)
{
    switch (subject) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
    default:
        return false;
    }
}

int isValidOperand(char subject)
{
    return islower(subject) > 0;
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

struct Stack {
    char *items;
    int index;
} Stack;

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    int inIndex = 0, outIndex = 0;
    char current, operator;
    char stackArray[length / 2];
    struct Stack operators = { stackArray, 0 };
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
                operators.items[operators.index++] = '(';
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
                while (!isEmpty(operators.index) && (operator = pop(operators.items, --operators.index)) != '(')
                    out[outIndex++] = operator;
                continue;
            }

            if (!isValidOperator(current))
                return RPN_PARSE_ERROR_INVALID_OPERATOR;

            while (!isEmpty(operators.index) && precedenceOf(current) < precedenceOf(operators.items[operators.index-1]))
                out[outIndex++] = pop(operators.items, --operators.index);

            operators.items[operators.index++] = current;

            expecting = OPERAND;
        }
    }

    while (operators.index >= 0 && outIndex < length)
        out[outIndex++] = pop(operators.items, --operators.index);

    return RPN_SUCCESS;
}
