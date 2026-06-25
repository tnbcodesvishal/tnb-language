#include "operators.h"
#include <stdio.h>
#include <stdlib.h>

AST_T* operator_modulo(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    if(left->type != AST_INT ||
       right->type != AST_INT)
    {
        printf("Modulo operator only supports integers\n");
        exit(1);
    }

    if(right->int_value == 0)
    {
        printf("Modulo by zero\n");
        exit(1);
    }

    AST_T* result = init_ast(AST_INT);

    result->int_value =
        left->int_value % right->int_value;

    return result;
}