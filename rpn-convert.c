#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "rpn-convert.h"
#include "rpn-string.h"

#define OPEN_PAREN '('
#define CLOSE_PAREN ')'

typedef enum { OPERAND, OPERATOR } SymbolType;

static int isValidOperator(char subject)
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

static int isValidOperand(char subject)
{
    return islower(subject) > 0;
}

static int precedenceOf(char subject)
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

static int halfOf(int value)
{
    return value / 2;
}

static RpnErrorType processOpenParen(char current, struct String *operators)
{
    push(operators, current);
    return RPN_SUCCESS;
}

static RpnErrorType processCloseParen(char current, struct String *operators, struct String *output)
{
    char operator;

    while (!isEmpty(operators) && (operator = pop(operators)) != OPEN_PAREN)
        push(output, operator);

    return operator == OPEN_PAREN ? RPN_SUCCESS : RPN_PARSE_ERROR_UNMATCHED_CLOSE_PAREN;
}

static RpnErrorType processOperand(char current, struct String *output)
{
    if (!isValidOperand(current))
        return RPN_PARSE_ERROR_INVALID_OPERAND;

    push(output, current);
    return RPN_SUCCESS;
}

static RpnErrorType processOperator(char current, struct String *operators, struct String *output)
{
    if (!isValidOperator(current))
        return RPN_PARSE_ERROR_INVALID_OPERATOR;

    while (!isEmpty(operators) && precedenceOf(current) < precedenceOf(head(operators)))
        push(output, pop(operators));

    push(operators, current);

    return RPN_SUCCESS;
}

static RpnErrorType processExpectedOperand(char current, struct String *operators, struct String *output, SymbolType *expecting)
{
    if (OPEN_PAREN == current)
        return processOpenParen(current, operators);

    *expecting = OPERATOR;
    return processOperand(current, output);
}

static RpnErrorType processExpectedOperator(char current, struct String *operators, struct String *output, SymbolType *expecting)
{
    if (CLOSE_PAREN == current)
        return processCloseParen(current, operators, output);

    *expecting = OPERAND;
    return processOperator(current, operators, output);
}

static RpnErrorType processCharacter(char current, struct String *operators, struct String *output, SymbolType *expecting)
{
    if (*expecting == OPERAND)
        return processExpectedOperand(current, operators, output, expecting);
    else
        return processExpectedOperator(current, operators, output, expecting);
}

static RpnErrorType concatRemainingOperators(struct String *operators, struct String *output)
{
    char operator;
    while (!isEmpty(operators) && !isFull(output)) {
        operator = pop(operators);
        if (operator == OPEN_PAREN)
            return RPN_PARSE_ERROR_UNMATCHED_OPEN_PAREN;
        push(output, operator);
    }
    return RPN_SUCCESS;
}

RpnErrorType infixToReversePolish(const char *in, char *out, int length)
{
    char operatorsChars[halfOf(length)];
    struct String operators = { operatorsChars, 0, halfOf(length) };
    struct String output = { out, 0, length };
    RpnErrorType result;
    SymbolType expecting = OPERAND;

    if (in == NULL || out == NULL || length < 1)
        return RPN_INVALID_ARGS;

    for (int i = 0; i < length && in[i] != END_OF_STRING; i++) {
        if ((result = processCharacter(in[i], &operators, &output, &expecting)) != RPN_SUCCESS)
            return result;
    }

    if ((result = concatRemainingOperators(&operators, &output)) != RPN_SUCCESS)
        return result;

    finish(&output);
    return RPN_SUCCESS;
}
