#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "convert-rpn.h"

struct Stack {
    char *items;
    int index;
} Stack;

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

int isEmpty(struct Stack *stack)
{
    return stack->index == 0;
}

char head(struct Stack *stack)
{
    return stack->items[stack->index-1];
}

void push(struct Stack *stack, char item)
{
    stack->items[stack->index] = item;
    stack->index++;
}

char pop(struct Stack *stack)
{
    stack->index--;
    char value = stack->items[stack->index];
    stack->items[stack->index] = '\0';
    return value;
}

int processOpenParen(struct Stack *operators, char current)
{
    if ('(' == current) {
        push(operators, '(');
        return 1;
    }
    return 0;
}

int processCloseParen(struct Stack *operators, char current, char *out, int *outIndex)
{
    char operator;
    if (')' == current) {
        while (!isEmpty(operators) && (operator = pop(operators)) != '(') {
            out[*outIndex] = operator;
            *outIndex += 1;
        }
        return 1;
    }
    return 0;
}

RpnErrorType processOperand(char current, char *out, int *outIndex)
{
    if (!isValidOperand(current))
        return RPN_PARSE_ERROR_INVALID_OPERAND;

    out[*outIndex] = current;
    *outIndex += 1;
    return RPN_SUCCESS;
}

RpnErrorType processOperator(struct Stack *operators, char current, char *out, int *outIndex)
{
    if (!isValidOperator(current))
        return RPN_PARSE_ERROR_INVALID_OPERATOR;

    while (!isEmpty(operators) && precedenceOf(current) < precedenceOf(head(operators))) {
        out[*outIndex] = pop(operators);
        *outIndex += 1;
    }

    push(operators, current);

    return RPN_SUCCESS;
}

RpnErrorType infixToReversePolish(char *in, char *out, int length)
{
    int inIndex = 0, outIndex = 0;
    char current;
    char stackArray[length / 2];
    struct Stack operators = { stackArray, 0 };
    RpnErrorType result;
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
            if (processOpenParen(&operators, current))
                continue;

            if ((result = processOperand(current, out, &outIndex)) != RPN_SUCCESS)
                return result;

            expecting = OPERATOR;
        }
        else if (expecting == OPERATOR)
        {
            if (processCloseParen(&operators, current, out, &outIndex))
                continue;

            if ((result = processOperator(&operators, current, out, &outIndex)) != RPN_SUCCESS)
                return result;

            expecting = OPERAND;
        }

    }

    while (!isEmpty(&operators) && outIndex < length - 1)
        out[outIndex++] = pop(&operators);

    out[outIndex] = '\0';

    return RPN_SUCCESS;
}
