#include "operators.h"

AST_T* operator_plus(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    double a =
        operator_get_number(left);

    double b =
        operator_get_number(right);

    return operator_create_number(
        a+b,
        operator_result_is_float(left,right)
    );
}