#include "comparison_utils.h"

#include <stdio.h>
#include <stdlib.h>

double comparison_get_number(AST_T* node)
{
    switch(node->type)
    {
        case AST_INT:
            return node->int_value;

        case AST_FLOAT:
            return node->float_value;

        default:
            printf("Comparison only supports numeric values\n");
            exit(1);
    }
}   