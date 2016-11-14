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

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    char c;

    if (in == NULL || out == NULL || length < 1) {
        return RPN_INVALID_ARGS;
    }

    for (int i = 0; (c = in[i]) != '\0' && i < length; i++) {
        if (isValidOperand(c)) {
            out[i] = c;
        } else {
            return RPN_PARSE_ERROR_INVALID_OPERAND;
        }
    }

    return RPN_SUCCESS;
}
