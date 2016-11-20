#ifndef RPN_STRING_H
#define RPN_STRING_H

#define END_OF_STRING '\0'

struct String {
    char *chars;
    int length;
    int size;
} String;

int isEmpty(struct String *string);
int isFull(struct String *string);
char head(struct String *string);
void push(struct String *string, char item);
char pop(struct String *string);
void finish(struct String *string);

#endif
