#include<stdio.h>

#include "include/lexer.h"
#include "include/parser.h"

#include "include/visitor.h"

#include "include/io.h"

void print_help(){
    // printf("Usage: \n tnb.out <main.tnb>\n");
}

int main(int argc, char *argv[]) {

    if(argc<2){
        print_help();
        return 1;
    }
    lexer_T *lexer = init_lexer(
        get_file_contents(argv[1])
    );

    parser_T *parser = init_parser(lexer);  
    AST_T *root = parser_parse(parser);
    visitor_T* visitor=init_visitor();
    visitor_visit(visitor, root);
    // printf("%d\n",root->type);
    // printf("%ld\n",root->compound_size);
    return 0;
}