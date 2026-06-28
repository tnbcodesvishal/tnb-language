#include "logical_utils.h"

#include <stdio.h>
#include <stdlib.h>

int logical_get_bool(AST_T* node)
{
    switch(node->type)
    {
        case AST_BOOL:
            return node->bool_value;

        case AST_INT:
            return node->int_value != 0;

        case AST_FLOAT:
            return node->float_value != 0.0f;

        default:
            printf("Logical operator expects bool/int/float\n");
            exit(1);
    }
}