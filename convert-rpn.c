#include "convert-rpn.h"

int isValidOperator(char *subject)
{
    if (subject[0] == '+') {
        return 1;
    }
    return 0;
}
