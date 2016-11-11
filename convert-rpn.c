#include "convert-rpn.h"

int isValidOperator(char subject)
{
    if ('+' == subject) {
        return 1;
    }
    return 0;
}
