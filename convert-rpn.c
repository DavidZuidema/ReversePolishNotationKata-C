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
    return string->length >= string->size;
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

int processOpenParen(struct String *operators, char current)
{
    if (OPEN_PAREN != current)
        return 0;

    push(operators, OPEN_PAREN);
    return 1;
}

int processCloseParen(struct String *operators, char current, struct String *output)
{
    char operator;

    if (CLOSE_PAREN != current)
        return 0;

    while (!isEmpty(operators) && (operator = pop(operators)) != OPEN_PAREN)
        push(output, operator);

    return 1;
}

RpnErrorType processOperand(char current, struct String *output)
{
    if (!isValidOperand(current))
        return RPN_PARSE_ERROR_INVALID_OPERAND;

    push(output, current);
    return RPN_SUCCESS;
}

RpnErrorType processOperator(struct String *operators, char current, struct String *output)
{
    if (!isValidOperator(current))
        return RPN_PARSE_ERROR_INVALID_OPERATOR;

    while (!isEmpty(operators) && precedenceOf(current) < precedenceOf(head(operators)))
        push(output, pop(operators));

    push(operators, current);

    return RPN_SUCCESS;
}

RpnErrorType infixToReversePolish(const char *in, char *out, int length)
{
    char current;
    char operatorsChars[halfOf(length)];
    struct String operators = { operatorsChars, 0, halfOf(length) };
    struct String output = { out, 0, length };
    RpnErrorType result;
    SymbolType expecting = OPERAND;

    if (in == NULL || out == NULL || length < 1)
        return RPN_INVALID_ARGS;

    for (int inIndex = 0; inIndex < length; inIndex++)
    {
        current = in[inIndex];

        if (current == END_OF_STRING)
            break;

        if (expecting == OPERAND)
        {
            if (processOpenParen(&operators, current))
                continue;

            if ((result = processOperand(current, &output)) != RPN_SUCCESS)
                return result;

            expecting = OPERATOR;
        }
        else if (expecting == OPERATOR)
        {
            if (processCloseParen(&operators, current, &output))
                continue;

            if ((result = processOperator(&operators, current, &output)) != RPN_SUCCESS)
                return result;

            expecting = OPERAND;
        }
    }

    while (!isEmpty(&operators) && !isFull(&output))
        push(&output, pop(&operators));

    push(&output, END_OF_STRING);

    return RPN_SUCCESS;
}
