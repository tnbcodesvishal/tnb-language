#include "operator_utils.h"

#include <stdlib.h>

double operator_get_number(AST_T* node)
{
    switch(node->type)
    {
        case AST_INT:
            return node->int_value;

        case AST_FLOAT:
            return node->float_value;
    }

    return 0;
}

int operator_result_is_float(
    AST_T* left,
    AST_T* right
)
{
    return left->type == AST_FLOAT ||
           right->type == AST_FLOAT;
}

AST_T* operator_create_number(
    double value,
    int is_float
)
{
    if(is_float)
    {
        AST_T* ast =
            init_ast(AST_FLOAT);

        ast->float_value = value;

        return ast;
    }

    AST_T* ast =
        init_ast(AST_INT);

    ast->int_value = (int)value;

    return ast;
}