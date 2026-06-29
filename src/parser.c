    #include "include/parser.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include<string.h>

    // parser_T* init_parser(lexer_T* lexer){
    //     parser_T* parser= calloc(1, sizeof(struct PARSER_STRUCT));
    //     parser->lexer=lexer;
    //     parser->current_token=lexer_get_next_token(lexer);
    //     parser->prev_token=parser->current_token; 

    //     return parser;
    // }

    parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser =
        calloc(1, sizeof(struct PARSER_STRUCT));

    parser->lexer = lexer;

    parser->prev_token = NULL;

    parser->current_token =
        lexer_get_next_token(lexer);

    parser->next_token =
        lexer_get_next_token(lexer);

    return parser;
}

    // void parser_eat(parser_T* parser, int token_type){

    //     if(parser->current_token->type == token_type){

    //         parser->prev_token = parser->current_token; 
    //         parser->current_token = lexer_get_next_token(parser->lexer);


    //     }else{
    //         printf("Syntax error: expected token type `%s`, got %d", 
    //         parser->current_token->value,
    //         parser->current_token->type

    // );

    //         exit(1);
    //     }
    // }

//     void parser_eat(
//     parser_T* parser,
//     int token_type
// )
// {
//     if(parser->current_token->type == token_type)
//     {
//         parser->prev_token =
//             parser->current_token;

//         parser->current_token =
//             parser->next_token;

//         parser->next_token =
//             lexer_get_next_token(parser->lexer);

//         return;
//     }

//     printf(
//         "Syntax error: expected token type %d, got %d\n",
//         token_type,
//         parser->current_token->type
//     );

//     exit(1);
// }

void parser_eat(parser_T* parser, int token_type)
{
    if(parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;

        parser->current_token = parser->next_token;

        parser->next_token =
            lexer_get_next_token(parser->lexer);

        return;
    }

    printf(
        "Syntax Error: Expected token %d, got %d (%s)\n",
        token_type,
        parser->current_token->type,
        parser->current_token->value
    );

    exit(1);
}
    AST_T* parser_parse(parser_T* parser){

        return parser_parse_statements(parser);

    }
AST_T* parser_parse_statement(parser_T* parser)
{
    if(parser->current_token->type == TOKEN_EOF)
        return NULL;

    switch(parser->current_token->type)
    {
        case TOKEN_ID:
            return parser_parse_id(parser);
    }

    return init_ast(AST_NOOP);
}
AST_T* parser_parse_statements(parser_T* parser)
{
    AST_T* compound = init_ast(AST_COMPOUND);

    compound->compound_value = NULL;
    compound->compound_size = 0;

    while(parser->current_token->type != TOKEN_EOF)
    {
        AST_T* stmt = parser_parse_statement(parser);

        compound->compound_size++;

        compound->compound_value = realloc(
            compound->compound_value,
            compound->compound_size * sizeof(AST_T*)
        );

        compound->compound_value[
            compound->compound_size - 1
        ] = stmt;

        if(parser->current_token->type == TOKEN_SEMI)
            parser_eat(parser, TOKEN_SEMI);
        else
            break;
    }

    return compound;
}


AST_T* parser_parse_expr(parser_T* parser)
{
    return parser_parse_logical(parser);
}

AST_T* parser_parse_logical(parser_T* parser)
{
    AST_T* left = parser_parse_comparison(parser);

    while(
        parser->current_token->type == TOKEN_AND ||
        parser->current_token->type == TOKEN_OR
    )
    {
        char* op = strdup(parser->current_token->value);

        if(parser->current_token->type == TOKEN_AND)
            parser_eat(parser, TOKEN_AND);
        else
            parser_eat(parser, TOKEN_OR);

        AST_T* right =
            parser_parse_comparison(parser);

        AST_T* binop =
            init_ast(AST_BINOP);

        binop->left = left;
        binop->right = right;
        binop->op = op;

        left = binop;
    }

    return left;
}

AST_T* parser_parse_comparison(parser_T* parser)
{
    AST_T* left = parser_parse_additive(parser);

    while(
        parser->current_token->type == TOKEN_EQUAL_EQUAL ||
        parser->current_token->type == TOKEN_NOT_EQUAL ||
        parser->current_token->type == TOKEN_GREATER ||
        parser->current_token->type == TOKEN_LESS ||
        parser->current_token->type == TOKEN_GREATER_EQUAL ||
        parser->current_token->type == TOKEN_LESS_EQUAL
    )
    {
        char* op = strdup(parser->current_token->value);

        switch(parser->current_token->type)
        {
            case TOKEN_EQUAL_EQUAL:
                parser_eat(parser, TOKEN_EQUAL_EQUAL);
                break;

            case TOKEN_NOT_EQUAL:
                parser_eat(parser, TOKEN_NOT_EQUAL);
                break;

            case TOKEN_GREATER:
                parser_eat(parser, TOKEN_GREATER);
                break;

            case TOKEN_LESS:
                parser_eat(parser, TOKEN_LESS);
                break;

            case TOKEN_GREATER_EQUAL:
                parser_eat(parser, TOKEN_GREATER_EQUAL);
                break;

            case TOKEN_LESS_EQUAL:
                parser_eat(parser, TOKEN_LESS_EQUAL);
                break;
        }

        AST_T* right =
            parser_parse_additive(parser);

        AST_T* binop =
            init_ast(AST_BINOP);

        binop->left = left;
        binop->right = right;
        binop->op = op;

        left = binop;
    }

    return left;
}

AST_T* parser_parse_factor(parser_T* parser)
{
    if(parser->current_token->type == TOKEN_PLUS)
    {
        parser_eat(parser, TOKEN_PLUS);

        AST_T* unary = init_ast(AST_UNARY);

        unary->unary_op = "+";
        unary->unary_value = parser_parse_factor(parser);

        return unary;
    }

    if(parser->current_token->type == TOKEN_MINUS)
    {
        parser_eat(parser, TOKEN_MINUS);

        AST_T* unary = init_ast(AST_UNARY);

        unary->unary_op = "-";
        unary->unary_value = parser_parse_factor(parser);

        return unary;
    }

    /* Logical NOT */

    if(parser->current_token->type == TOKEN_NOT)
    {
        parser_eat(parser, TOKEN_NOT);

        AST_T* unary = init_ast(AST_UNARY);

        unary->unary_op = "!";
        unary->unary_value = parser_parse_factor(parser);

        return unary;
    }

    if(parser->current_token->type == TOKEN_LPAREN)
    {
        parser_eat(parser, TOKEN_LPAREN);

        AST_T* expr = parser_parse_expr(parser);

        parser_eat(parser, TOKEN_RPAREN);

        return expr;
    }

    switch(parser->current_token->type)
    {
        case TOKEN_STRING:
            return parser_parse_string(parser);

        case TOKEN_INT:
            return parser_parse_int(parser);

        case TOKEN_FLOAT:
            return parser_parse_float(parser);

        case TOKEN_CHAR:
            return parser_parse_char(parser);

        case TOKEN_TRUE:
        case TOKEN_FALSE:
            return parser_parse_bool(parser);

        case TOKEN_ID:
            return parser_parse_id(parser);
    }

    return init_ast(AST_NOOP);
}


   AST_T* parser_parse_term(parser_T* parser)
{
  AST_T* left = parser_parse_factor(parser);

    while(
        parser->current_token->type == TOKEN_MUL ||
        parser->current_token->type == TOKEN_DIV||
        parser->current_token->type == TOKEN_MOD
    )
    {
        char* op = strdup(parser->current_token->value);

        if(parser->current_token->type == TOKEN_MUL)
            parser_eat(parser, TOKEN_MUL);
        else if(parser->current_token->type == TOKEN_DIV)
            parser_eat(parser,TOKEN_DIV);
        else
            parser_eat(parser, TOKEN_MOD);

        AST_T* right = parser_parse_factor(parser);

        AST_T* binop = init_ast(AST_BINOP);

        binop->left = left;
        binop->right = right;
        binop->op = op;

        left = binop;
    }

    return left;
}

AST_T* parser_parse_additive(parser_T* parser)
{
    AST_T* left = parser_parse_term(parser);

    while(
        parser->current_token->type == TOKEN_PLUS ||
        parser->current_token->type == TOKEN_MINUS
    )
    {
        char* op = strdup(parser->current_token->value);

        if(parser->current_token->type == TOKEN_PLUS)
            parser_eat(parser, TOKEN_PLUS);
        else
            parser_eat(parser, TOKEN_MINUS);

        AST_T* right = parser_parse_term(parser);

        AST_T* binop = init_ast(AST_BINOP);

        binop->left = left;
        binop->right = right;
        binop->op = op;

        left = binop;
    }

    return left;
}
        
AST_T* parser_parse_function_call(parser_T* parser)
{
    AST_T* function_call =
        init_ast(AST_FUNCTION_CALL);

    function_call->function_call_name =
        strdup(parser->current_token->value);

    parser_eat(parser, TOKEN_ID);
    parser_eat(parser, TOKEN_LPAREN);

    function_call->function_call_arguments =
        calloc(1, sizeof(AST_T*));

    function_call->function_call_arguments_size = 0;

    if(parser->current_token->type != TOKEN_RPAREN)
    {
        AST_T* ast_expr =
            parser_parse_expr(parser);

        function_call->function_call_arguments[
            function_call->function_call_arguments_size++
        ] = ast_expr;

        while(parser->current_token->type == TOKEN_COMMA)
        {
            parser_eat(parser, TOKEN_COMMA);

            ast_expr = parser_parse_expr(parser);

            function_call->function_call_arguments =
                realloc(
                    function_call->function_call_arguments,
                    sizeof(AST_T*) *
                    (function_call->function_call_arguments_size + 1)
                );

            function_call->function_call_arguments[
                function_call->function_call_arguments_size++
            ] = ast_expr;
        }
    }

    parser_eat(parser, TOKEN_RPAREN);

    return function_call;
}

    // AST_T* parser_parse_variable_defination(parser_T* parser){

    //     parser_eat(parser, TOKEN_ID); // eat var

    //     char* variable_defination_variable_name=parser->current_token->value;
    //     parser_eat(parser, TOKEN_ID); // eat variable name

    //     parser_eat(parser, TOKEN_EQUALS); // eat =

    //     AST_T* variable_defination_value=parser_parse_expr(parser);

    //     AST_T* variable_defination=init_ast(AST_VARIABLE_DECLARATION);
    //     variable_defination->variable_defination_variable_name=variable_defination_variable_name;
    //     variable_defination->variable_defination_value=variable_defination_value;

    

    //     return variable_defination;
    // }

AST_T* parser_parse_variable_defination(parser_T* parser)
{
    parser_eat(parser, TOKEN_ID); // eat var

    char* variable_defination_variable_name =
        strdup(parser->current_token->value);

    parser_eat(parser, TOKEN_ID); // eat variable name

    AST_T* variable_defination_value = NULL;

    if(parser->current_token->type == TOKEN_EQUALS)
    {
        parser_eat(parser, TOKEN_EQUALS);

        variable_defination_value =
            parser_parse_expr(parser);
    }

    AST_T* variable_defination =
        init_ast(AST_VARIABLE_DECLARATION);

    variable_defination->variable_defination_variable_name =
        variable_defination_variable_name;

    variable_defination->variable_defination_value =
        variable_defination_value;

    return variable_defination;
}
    
AST_T* parser_parse_variable(parser_T* parser)
{
    if(
        parser->next_token != NULL &&
        parser->next_token->type == TOKEN_LPAREN
    )
    {
        return parser_parse_function_call(parser);
    }

    AST_T* ast_variable = init_ast(AST_VARIABLE);

    ast_variable->variable_name =
        strdup(parser->current_token->value);

    parser_eat(parser, TOKEN_ID);

    return ast_variable;
}
    AST_T* parser_parse_string(parser_T* parser){
        AST_T* ast_string=init_ast(AST_STRING);
        ast_string->string_value=parser->current_token->value;
        parser_eat(parser, TOKEN_STRING); // eat string
        return ast_string;
    }

    // AST_T* parser_parse_id(parser_T* parser){
    //     if(strcmp(parser->current_token->value, "var")==0){
    //         return parser_parse_variable_defination(parser);    
    //         }else{
    //             return parser_parse_variable(parser);      
    //     }
    // }

    AST_T* parser_parse_id(parser_T* parser)
{
    /* Variable declaration */

    if(strcmp(parser->current_token->value, "var") == 0)
    {
        return parser_parse_variable_defination(parser);
    }

    /* Variable assignment */

    if(
        parser->next_token != NULL &&
        parser->next_token->type == TOKEN_EQUALS
    )
    {
        return parser_parse_variable_assignment(parser);
    }

    /* Variable / Function */

    return parser_parse_variable(parser);
}

    AST_T* parser_parse_int(parser_T* parser)
    {
        AST_T* ast = init_ast(AST_INT);

        ast->int_value = atoi(parser->current_token->value);

        parser_eat(parser, TOKEN_INT);

        return ast;
    }

    AST_T* parser_parse_float(parser_T* parser)
    {
        AST_T* ast = init_ast(AST_FLOAT);

        ast->float_value =
            atof(parser->current_token->value);

        parser_eat(parser, TOKEN_FLOAT);

        return ast;
    }

    AST_T* parser_parse_char(parser_T* parser)
    {
        AST_T* ast = init_ast(AST_CHAR);

        ast->char_value =
            parser->current_token->value[0];

        parser_eat(parser, TOKEN_CHAR);

        return ast;
    }

    AST_T* parser_parse_bool(parser_T* parser)
{
    AST_T* ast = init_ast(AST_BOOL);

    if(parser->current_token->type == TOKEN_TRUE)
    {
        ast->bool_value = 1;
        parser_eat(parser, TOKEN_TRUE);
    }
    else
    {
        ast->bool_value = 0;
        parser_eat(parser, TOKEN_FALSE);
    }

    return ast;
}

AST_T* parser_parse_variable_assignment(parser_T* parser)
{
    AST_T* ast =
        init_ast(AST_VARIABLE_ASSIGNMENT);

    ast->variable_assignment_variable_name =
        strdup(parser->current_token->value);

    parser_eat(parser, TOKEN_ID);

    parser_eat(parser, TOKEN_EQUALS);

    ast->variable_assignment_value =
        parser_parse_expr(parser);

    return ast;
}