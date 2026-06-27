#include "logical.h"

#include <stdio.h>
#include <stdlib.h>

AST_T* logical_and(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    AST_T* result = init_ast(AST_BOOL);

    result->bool_value =
        left->bool_value &&
        right->bool_value;

    return result;
}