#include "logical.h"

AST_T* logical_and(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    AST_T* result = init_ast(AST_BOOL);

    result->bool_value =
        logical_get_bool(left) &&
        logical_get_bool(right);

    return result;
}