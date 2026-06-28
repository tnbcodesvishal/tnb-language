#include "comparisons.h"
#include <stdio.h>

AST_T* comparison_not_equal(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    // printf("INSIDE comparison_not_equal\n");

    // printf("LEFT TYPE = %d\n", left->type);
    // printf("RIGHT TYPE = %d\n", right->type);

    double a = comparison_get_number(left);
    double b = comparison_get_number(right);

    // printf("a = %f\n", a);
    // printf("b = %f\n", b);

    AST_T* result = init_ast(AST_BOOL);

    result->bool_value = (a != b);

    // printf("RESULT = %d\n", result->bool_value);

    return result;
}