#include "rpn-string.h"

int isEmptyString(struct String *string)
{
    return string->length == 0;
}

int isFullString(struct String *string)
{
    return string->length >= string->size - 1;
}

char lastCharOfString(struct String *string)
{
    return string->chars[string->length-1];
}

void pushString(struct String *string, char item)
{
    if (isFullString(string))
        return;

    string->chars[string->length] = item;
    string->length++;
}

char popString(struct String *string)
{
    char character;

    if (isEmptyString(string))
        return END_OF_STRING;

    string->length--;
    character = string->chars[string->length];
    string->chars[string->length] = END_OF_STRING;
    return character;
}

void terminateString(struct String *string)
{
    pushString(string, END_OF_STRING);
}
