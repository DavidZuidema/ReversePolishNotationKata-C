#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "convert-rpn.h"

#define END_OF_STRING '\0'
#define OPEN_PAREN '('
#define CLOSE_PAREN ')'

struct String {
    char *chars;
    int length;
    int size;
} String;

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

int halfOf(int value)
{
    return value / 2;
}

int isEmpty(struct String *string)
{
    return string->length == 0;
}

int isFull(struct String *string)
{
    return string->length >= string->size - 1;
}

char head(struct String *string)
{
    return string->chars[string->length-1];
}

void push(struct String *string, char item)
{
    string->chars[string->length] = item;
    string->length++;
}

char pop(struct String *string)
{
    string->length--;
    char character = string->chars[string->length];
    string->chars[string->length] = END_OF_STRING;
    return character;
}

void finish(struct String *string)
{
    push(string, END_OF_STRING);
}

static int processOpenParen(char current, struct String *operators)
{
    if (OPEN_PAREN != current)
        return 0;

    push(operators, OPEN_PAREN);
    return 1;
}

static int processCloseParen(char current, struct String *operators, struct String *output)
{
    char operator;

    if (CLOSE_PAREN != current)
        return 0;

    while (!isEmpty(operators) && (operator = pop(operators)) != OPEN_PAREN)
        push(output, operator);

    return 1;
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
    if (processOpenParen(current, operators))
        return RPN_SUCCESS;

    *expecting = OPERATOR;
    return processOperand(current, output);
}

static RpnErrorType processExpectedOperator(char current, struct String *operators, struct String *output, SymbolType *expecting)
{
    if (processCloseParen(current, operators, output))
        return RPN_SUCCESS;

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

static void concatRemainingOperators(struct String *operators, struct String *output)
{
    while (!isEmpty(operators) && !isFull(output))
        push(output, pop(operators));
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

    for (int i = 0; i < length && in[i] != END_OF_STRING; i++)
    {
        if ((result = processCharacter(in[i], &operators, &output, &expecting)) != RPN_SUCCESS)
            return result;
    }
    concatRemainingOperators(&operators, &output);
    finish(&output);
    return RPN_SUCCESS;
}
