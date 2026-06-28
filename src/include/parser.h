#ifndef PARSER_H
#define PARSER_H
#include "AST.h"
#include "lexer.h"

typedef struct PARSER_STRUCT
{
     lexer_T* lexer;

    token_T* prev_token;
    token_T* current_token;
    token_T* next_token;
}parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_eat(parser_T* parser, int token_type);

AST_T* parser_parse(parser_T* parser);
AST_T* parser_parse_statement(parser_T* parser);
AST_T* parser_parse_statements(parser_T* parser);
AST_T* parser_parse_expr(parser_T* parser);
AST_T* parser_parse_factor(parser_T* parser);
AST_T* parser_parse_term(parser_T* parser);
 
AST_T* parser_parse_function_call(parser_T* parser);

AST_T* parser_parse_variable_defination(parser_T* parser);
 
AST_T* parser_parse_variable(parser_T* parser);
AST_T* parser_parse_string(parser_T* parser);

AST_T* parser_parse_int(parser_T* parser);
AST_T* parser_parse_float(parser_T* parser);

AST_T* parser_parse_char(parser_T* parser);

AST_T* parser_parse_id(parser_T* parser);


 AST_T* parser_parse_bool(parser_T* parser);

 AST_T* parser_parse_variable_assignment(parser_T* parser);

 AST_T* parser_parse_logical(parser_T* parser);


 AST_T* parser_parse_comparison(parser_T* parser);

AST_T* parser_parse_additive(parser_T* parser);





#endif