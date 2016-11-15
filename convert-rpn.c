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
    return 0;
}

typedef enum { OPERAND, OPERATOR } SymbolType;

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    int inIndex = 0, outIndex = 0;
    char current, operator;
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

            if (operator != '\0')
            {
                out[outIndex++] = operator;
                operator = '\0';
            }
        }
        else if (expecting == OPERATOR)
        {
            if (!isValidOperator(current))
                return RPN_PARSE_ERROR_INVALID_OPERATOR;

            operator = current;
            expecting = OPERAND;
        }
    }

    return RPN_SUCCESS;
}
