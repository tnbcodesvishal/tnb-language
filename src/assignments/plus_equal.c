#include "assignments.h"
#include "../operators/operators.h"

AST_T* assignment_plus_equal(
    visitor_T* visitor,
    AST_T* vardef,
    AST_T* value
)
{
    AST_T* left =
        visitor_visit(
            visitor,
            vardef->variable_defination_value
        );

    AST_T* right =
        visitor_visit(
            visitor,
            value
        );

    AST_T* result =
        operator_plus(
            visitor,
            left,
            right
        );

    vardef->variable_defination_value = result;

    return result;
}