#include "comparisons.h"

AST_T* comparison_greater_equal(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    AST_T* result = init_ast(AST_BOOL);

    double a = comparison_get_number(left);
    double b = comparison_get_number(right);

    result->bool_value = (a >= b);

    return result;
}