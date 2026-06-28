#include "comparison_utils.h"

#include <stdio.h>
#include <stdlib.h>

double comparison_get_number(AST_T* node)
{
    // printf("TYPE = %d\n", node->type);

    switch(node->type)
    {
        case AST_INT:
            // printf("INT = %d\n", node->int_value);
            return node->int_value;

        case AST_FLOAT:
            // printf("FLOAT = %f\n", node->float_value);
            return node->float_value;

        default:
            printf("INVALID TYPE\n");
            exit(1);
    }
}