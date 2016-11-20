#include "rpn-string.h"

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
