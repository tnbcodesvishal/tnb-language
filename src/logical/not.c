#include "logical.h"

AST_T* logical_not(
    visitor_T* visitor,
    AST_T* value
)
{
    AST_T* result = init_ast(AST_BOOL);

    result->bool_value = !value->bool_value;

    return result;
}