#include "convert-rpn.h"

int isValidOperator(char subject)
{
    switch (subject) {
    case '+':
    case '-':
    case '*':
    case '/':
        return 1;
    default:
        return 0;
    }
}
