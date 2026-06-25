#include "operators.h"

#include <stdio.h>
#include <stdlib.h>

AST_T* operator_divide(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    double a =
        operator_get_number(left);

    double b =
        operator_get_number(right);

    if(b==0)
    {
        printf("Division by zero\n");
        exit(1);
    }

    return operator_create_number(
        a/b,
        operator_result_is_float(left,right)
    );
}