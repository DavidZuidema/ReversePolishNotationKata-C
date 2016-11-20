#ifndef RPN_CONVERT_H
#define RPN_CONVERT_H

typedef enum {
    RPN_SUCCESS,
    RPN_INVALID_ARGS,
    RPN_PARSE_ERROR_INVALID_OPERAND,
    RPN_PARSE_ERROR_INVALID_OPERATOR,
    RPN_PARSE_ERROR_UNMATCHED_OPEN_PAREN,
    RPN_PARSE_ERROR_UNMATCHED_CLOSE_PAREN
} RpnErrorType;

RpnErrorType infixToReversePolish(const char *in, char *out, int length);

#endif
