#ifndef RPN_STRING_H
#define RPN_STRING_H

#define END_OF_STRING '\0'

struct String {
    char *chars;
    int length;
    int size;
} String;

int isEmptyString(struct String *string);
int isFullString(struct String *string);
char lastCharOfString(struct String *string);
void pushString(struct String *string, char item);
char popString(struct String *string);
void terminateString(struct String *string);

#endif
