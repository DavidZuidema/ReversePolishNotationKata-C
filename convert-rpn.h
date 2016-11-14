#ifndef CONVERT_RPN_H
#define CONVERT_RPN_H

typedef enum { RPN_SUCCESS, RPN_INVALID_ARGS } RpnErrorType;

int isValidOperator(char subject);
int isValidOperand(char subject);
RpnErrorType infixToReversePolish(char *in, char *out, int length);

#endif
