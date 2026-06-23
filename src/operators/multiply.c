#include "operators.h"
#include <stdio.h>
#include <stdlib.h>

AST_T* operator_multiply(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
)
{
    if(
        left->type == AST_INT &&
        right->type == AST_INT
    )
    {
        AST_T* result = init_ast(AST_INT);

        result->int_value =
            left->int_value *
            right->int_value;

        return result;
    }

    printf("Unsupported * operation\n");
    exit(1);
}