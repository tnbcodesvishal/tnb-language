#include "logical.h"

AST_T* logical_not(
    visitor_T* visitor,
    AST_T* value
)
{
    AST_T* result = init_ast(AST_BOOL);

    result->bool_value =
        !logical_get_bool(value);

    return result;
}