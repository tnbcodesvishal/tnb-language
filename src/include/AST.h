#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include<ctype.h>

typedef struct AST_STRUCT
{
    enum
    {
        AST_VARIABLE_DECLARATION,
        AST_VARIABLE,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_COMPOUND,
        AST_BINOP,
        AST_NOOP,
    
    } type;

    char* variable_defination_variable_name;
    struct AST_STRUCT* variable_defination_value;

    char* variable_name;
    char* function_call_name;
    struct AST_STRUCT** function_call_arguments;
    size_t function_call_arguments_size;

    
    char* string_value;

    struct AST_STRUCT** compound_value;
    size_t compound_size;

}AST_T;

AST_T* init_ast(int type);
#endif