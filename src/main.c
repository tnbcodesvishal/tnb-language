#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

void print_help()
{
    printf("Usage:\n");
    printf("tnb <file.tnb>\n");
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        print_help();
        return 1;
    }

    char* filename = argv[1];

    char* ext = strrchr(filename, '.');

    if(ext == NULL || strcmp(ext, ".tnb") != 0)
    {
        printf(
            "Error: '%s' is not a .tnb file\n",
            filename
        );

        return 1;
    }

    lexer_T* lexer = init_lexer(
        get_file_contents(filename)
    );

    parser_T* parser = init_parser(lexer);

    AST_T* root = parser_parse(parser);

    visitor_T* visitor = init_visitor();

    visitor_visit(visitor, root);

    return 0;
}