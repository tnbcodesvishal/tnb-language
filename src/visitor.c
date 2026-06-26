#include "include/Visitor.h"

#include <stdio.h>
#include <string.h>
#include "operators/operators.h"
#include "comparisons/comparisons.h"

#include "builtins/builtins.h"


visitor_T* init_visitor(){
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variables_definations=calloc(1, sizeof(struct AST_STRUCT*));
    visitor->variables_definations=(void *) 0;
    visitor->variables_definations_size=0;

    return visitor; 
}


AST_T* visitor_visit(visitor_T* visitor, AST_T* node){


    switch (node->type)
    {
            case AST_VARIABLE_DECLARATION:
                return visitor_visit_variable_defination(visitor, node);
                break;

            case AST_VARIABLE:
                return visitor_visit_variable(visitor, node);
                break;

            case AST_FUNCTION_CALL:
                return visitor_visit_function_call(visitor, node);
                break;

            case AST_STRING:
                return visitor_visit_string(visitor, node);
                break;
            case AST_COMPOUND:
                return visitor_visit_compound(visitor, node);
                break;

            case AST_INT:
                 return visitor_visit_int(visitor, node);
                 break;

            case AST_FLOAT:
                 return visitor_visit_float(visitor, node);
                 break;

            case AST_CHAR:
             return visitor_visit_char(visitor,node);
             break;

             case AST_BINOP:
        return visitor_visit_binop(visitor, node);
        break;

        case AST_UNARY:
        return visitor_visit_unary(visitor, node);
        break;

        case AST_BOOL:
        return visitor_visit_bool(visitor, node);
        break;

            case AST_NOOP:
                return node;
                break;


    }           

    printf("uncaught statement of type %d\n", node->type);
    exit(1);
    return init_ast(AST_NOOP);


}



AST_T* visitor_visit_variable_defination(visitor_T* visitor,
                                         AST_T* node)
{
    for(int i = 0;
        i < visitor->variables_definations_size;
        i++)
    {
        AST_T* vardef =
            visitor->variables_definations[i];

        if(strcmp(
                vardef->variable_defination_variable_name,
                node->variable_defination_variable_name
           ) == 0)
        {
            printf(
                "Error: Variable '%s' already declared\n",
                node->variable_defination_variable_name
            );

            exit(1);
        }
    }

    if(visitor->variables_definations == (void*)0)
    {
        visitor->variables_definations =
            calloc(1, sizeof(struct AST_STRUCT*));

        visitor->variables_definations[0] = node;

        visitor->variables_definations_size = 1;
    }
    else
    {
        visitor->variables_definations_size++;

        visitor->variables_definations =
            realloc(
                visitor->variables_definations,
                visitor->variables_definations_size *
                sizeof(struct AST_STRUCT*)
            );

        visitor->variables_definations[
            visitor->variables_definations_size - 1
        ] = node;
    }

    return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node){

    for(int i=0;i<visitor->variables_definations_size;i++){
        AST_T* vardef=visitor->variables_definations[i];

        if(strcmp(vardef->variable_defination_variable_name, node->variable_name)==0){
            return visitor_visit(visitor, vardef->variable_defination_value);
        }
    }

    printf("undefined variable: %s\n", node->variable_name);
    return node;

}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node){

    if(strcmp(node->function_call_name, "print")==0){
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    printf("undefined function: %s\n", node->function_call_name);
    exit(1);
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node){

    return node;

}

AST_T* visitor_visit_int(visitor_T* visitor, AST_T* node)
{
    return node;
}


AST_T* visitor_visit_float(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_char(visitor_T* visitor,AST_T* node)
{
    return node;
}
AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node){

    for(int i=0; i<node->compound_size; i++){

        // printf("visiting compound node %d\n", i);
        visitor_visit(visitor, node->compound_value[i]);
    } 

    return init_ast(AST_NOOP);
    
}

AST_T* visitor_visit_binop(
visitor_T* visitor,
AST_T* node
)
{
AST_T* left =
visitor_visit(visitor, node->left);

AST_T* right =
    visitor_visit(visitor, node->right);

if(strcmp(node->op, "+") == 0)
{
    return operator_plus(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op, "-") == 0)
{
    return operator_minus(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op, "*") == 0)
{
    return operator_multiply(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op, "/")==0){
    return operator_divide(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op, "%") == 0)
{
    return operator_modulo(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op,"==")==0)
{
    return comparison_equal(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op,"!=")==0){
    return comparison_not_equal(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op, ">") == 0)
{
    return comparison_greater(
        visitor,
        left,
        right
    );
}

if(strcmp(node->op, "<") == 0)
{
    return comparison_less(
        visitor,
        left,
        right
    );
}



printf("Unknown operator: %s\n", node->op);
exit(1);

}

AST_T* visitor_visit_unary(
    visitor_T* visitor,
    AST_T* node
)
{
    AST_T* value =
        visitor_visit(
            visitor,
            node->unary_value
        );

    if(strcmp(node->unary_op,"+")==0)
    {
        return value;
    }

    if(strcmp(node->unary_op,"-")==0)
    {
        if(value->type == AST_INT)
        {
            AST_T* result =
                init_ast(AST_INT);

            result->int_value =
                -value->int_value;

            return result;
        }

        if(value->type == AST_FLOAT)
        {
            AST_T* result =
                init_ast(AST_FLOAT);

            result->float_value =
                -value->float_value;

            return result;
        }
    }

    printf("Unknown unary operator\n");
    exit(1);
}

AST_T* visitor_visit_bool(
    visitor_T* visitor,
    AST_T* node
)
{
    return node;
}