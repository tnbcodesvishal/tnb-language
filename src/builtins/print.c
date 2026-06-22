#include "print.h"
#include <stdio.h>

AST_T* builtin_function_print(
    visitor_T* visitor,
    AST_T** args,
    int args_size
)
{
    for(int i = 0; i < args_size; i++)
    {
        AST_T* visited_ast =
            visitor_visit(visitor, args[i]);

        switch(visited_ast->type)
        {
            case AST_STRING:
                printf("%s\n",
                       visited_ast->string_value);
                break;

            case AST_INT:
                printf("%d\n",
                       visited_ast->int_value);
                break;

            case AST_FLOAT:
                printf("%f\n",
                       visited_ast->float_value);
                break;

            case AST_CHAR:
                printf("%c\n",
                       visited_ast->char_value);
                break;

            default:
                printf("%p\n",
                       visited_ast);
                break;
        }
    }

    return init_ast(AST_NOOP);
}