#include "comparisons.h"

#include <stdio.h>

AST_T* comparison_greater(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    // printf("LEFT TYPE = %d\n", left->type);
    // printf("RIGHT TYPE = %d\n", right->type);

    // printf("LEFT INT = %d\n", left->int_value);
    // printf("RIGHT INT = %d\n", right->int_value);

    double a = comparison_get_number(left);
    double b = comparison_get_number(right);

    // printf("a = %f\n", a);
    // printf("b = %f\n", b);

    AST_T* result = init_ast(AST_BOOL);

    result->bool_value = (a > b);

    // printf("RESULT = %d\n", result->bool_value);

    return result;
}