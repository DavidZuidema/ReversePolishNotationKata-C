#ifndef CONVERT_RPN_H
#define CONVERT_RPN_H

typedef enum { RPN_SUCCESS, RPN_INVALID_ARGS, RPN_PARSE_ERROR_INVALID_OPERAND } RpnErrorType;

int isValidOperator(char subject);
int isValidOperand(char subject);
RpnErrorType infixToReversePolish(char *in, char *out, int length);

#endif
