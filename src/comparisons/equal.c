#include "comparisons.h"
#include <stdio.h>

AST_T* comparison_equal(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    AST_T* result = init_ast(AST_BOOL);

    double a = comparison_get_number(left);
    double b = comparison_get_number(right);

    result->bool_value = (a == b);

    // printf("a = %f\n", a);
    // printf("b = %f\n", b);
    // printf("bool = %d\n", result->bool_value);

    return result;
}