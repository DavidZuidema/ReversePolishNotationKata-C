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
    if (93 < subject && subject < 123)
        return 1;
    return 0;
}

typedef enum { OPERAND, OPERATOR } SymbolType;

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    int outIndex = 0;
    char c, operator;
    SymbolType expecting = OPERAND;

    if (in == NULL || out == NULL || length < 1) {
        return RPN_INVALID_ARGS;
    }

    for (int inIndex = 0; (c = in[inIndex]) != '\0' && inIndex < length; inIndex++) {
        if (expecting == OPERAND) {
            if (!isValidOperand(c))
                return RPN_PARSE_ERROR_INVALID_OPERAND;
            out[outIndex++] = c;
            if (operator != '\0') {
                out[outIndex++] = operator;
                operator = '\0';
            }
            expecting = OPERATOR;
            continue;
        }

        if (expecting == OPERATOR) {
            operator = c;
            expecting = OPERAND;
            continue;
        }
    }

    return RPN_SUCCESS;
}
