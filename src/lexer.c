// #include "include/lexer.h"
// #include <stdlib.h> 
// #include <string.h>
// #include <ctype.h>

// lexer_T *init_lexer(char *contents){
//     lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));
//     lexer->contents = contents;
//     lexer->i = 0;
//     lexer->c = contents[lexer->i];
//     return lexer;
// }

// void lexer_advance(lexer_T *lexer){

//     if(lexer->c != '\0' && lexer->i < strlen(lexer->contents)){
//         lexer->i +=1;
//         lexer->c = lexer->contents[lexer->i];
//     }
    

// }

// void lexer_skip_whitespace(lexer_T *lexer){

//     while(lexer->c == ' ' || lexer->c ==10){
//         lexer_advance(lexer);   
//     }
// }

// token_T *lexer_get_next_token(lexer_T *lexer){

//     while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)){
//         if(lexer->c == ' ' || lexer->c ==10){
//             lexer_skip_whitespace(lexer);
            
//         }

//             if(isalnum(lexer->c)){
//                 return lexer_collect_id(lexer);
//             }


//             if(lexer->c =='"'){
//                 return lexer_collect_string(lexer);
//             }


//             switch (lexer->c)
//             {            case '=': return lexer_advance_with_token(lexer,init_token(TOKEN_EQUALS,lexer_get_current_char_as_string(lexer)));  break;    
//                       case ';': return lexer_advance_with_token(lexer,init_token(TOKEN_SEMI,lexer_get_current_char_as_string(lexer)));   break;
//                              case '(': return lexer_advance_with_token(lexer,init_token(TOKEN_LPAREN,lexer_get_current_char_as_string(lexer)));  break;
//                                case ')': return lexer_advance_with_token(lexer,init_token(TOKEN_RPAREN,lexer_get_current_char_as_string(lexer)));  break;
//                                case ',': return lexer_advance_with_token(lexer,init_token(TOKEN_COMMA,lexer_get_current_char_as_string(lexer)));  break;

//         }

    

// }
// return init_token(TOKEN_EOF, "\0");
//     }   

// token_T *lexer_collect_string(lexer_T *lexer){

//     lexer_advance(lexer); // skip the opening quote

//     char *value=calloc(1, sizeof(char));    
//     value[0] = '\0'; 
    

//     while(lexer->c !='"'){
//         char *s=lexer_get_current_char_as_string(lexer);
//         value = realloc(value, strlen(value) + strlen(s) + 1*sizeof(char));  
//         strcat(value, s);
//     lexer_advance(lexer); 
//     }
//     lexer_advance(lexer); 
//     return init_token(TOKEN_STRING, value); 


// }


// token_T *lexer_collect_id(lexer_T *lexer){
//          // skip the opening quote

//     char *value=calloc(1, sizeof(char));    
//     value[0] = '\0'; 
    

//     while(isalnum(lexer->c)){
//             char *s=lexer_get_current_char_as_string(lexer);
//         value = realloc(value, strlen(value) + strlen(s) + 1*sizeof(char));  
//         strcat(value, s);
//     lexer_advance(lexer); 
//     }
    
//     return init_token(TOKEN_ID, value); 
// }

// token_T *lexer_advance_with_token(lexer_T *lexer, token_T *token){
//     lexer_advance(lexer);
//     return token;
// }

// char* lexer_get_current_char_as_string(lexer_T *lexer){

//     char *str = calloc(2, sizeof(char));
//     str[0] = lexer->c;
//     str[1] = '\0';
//     return str;
// }


#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

lexer_T *init_lexer(char *contents)
{
    lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));

    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[0];

    return lexer;
}

void lexer_advance(lexer_T *lexer)
{
    if (lexer->c != '\0')
    {
        lexer->i++;

        if (lexer->i >= strlen(lexer->contents))
        {
            lexer->c = '\0';
            return;
        }

        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T *lexer)
{
    while (lexer->c != '\0' && isspace((unsigned char)lexer->c))
    {
        lexer_advance(lexer);
    }
}

token_T *lexer_get_next_token(lexer_T *lexer)
{
    while (lexer->c != '\0')
    {

        if(
    lexer->c == '@' &&
    lexer->contents[lexer->i + 1] == '@'
)
{
    lexer_skip_multiline_comment(lexer);
    continue;
}

        if(lexer->c == '@')
{
    lexer_skip_comment(lexer);
    continue;
}




        if (isspace((unsigned char)lexer->c))
        {
            lexer_skip_whitespace(lexer);
            continue;
        }

                 if(isdigit((unsigned char)lexer->c)){

        
             return lexer_collect_number(lexer);
         } 
       

        if (isalnum((unsigned char)lexer->c))
        {
            return lexer_collect_id(lexer);
        }

      

        if (lexer->c == '"')
        {
            return lexer_collect_string(lexer);
        }

     if(lexer->c == '\'')
{
    return lexer_collect_char(lexer);
}

        switch (lexer->c)
        {
            case '=':
                return lexer_advance_with_token(
                    lexer,
                    init_token(TOKEN_EQUALS,
                    lexer_get_current_char_as_string(lexer))
                );

            case ';':
                return lexer_advance_with_token(
                    lexer,
                    init_token(TOKEN_SEMI,
                    lexer_get_current_char_as_string(lexer))
                );

            case '(':
                return lexer_advance_with_token(
                    lexer,
                    init_token(TOKEN_LPAREN,
                    lexer_get_current_char_as_string(lexer))
                );

            case ')':
                return lexer_advance_with_token(
                    lexer,
                    init_token(TOKEN_RPAREN,
                    lexer_get_current_char_as_string(lexer))
                );

            case ',':
                return lexer_advance_with_token(
                    lexer,
                    init_token(TOKEN_COMMA,
                    lexer_get_current_char_as_string(lexer))
                );

            case '+':
    return lexer_advance_with_token(
        lexer,
        init_token(
            TOKEN_PLUS,
            lexer_get_current_char_as_string(lexer)
        )
    );

    case '-':
    return lexer_advance_with_token(
        lexer,
        init_token(
            TOKEN_MINUS,
            lexer_get_current_char_as_string(lexer)
        )
    );

    case '*':
    return lexer_advance_with_token(
        lexer,
        init_token(
            TOKEN_MUL,
            lexer_get_current_char_as_string(lexer)
        )
    );
        }

        printf("Lexer Error: Unknown character '%c' (%d)\n",
               lexer->c,
               lexer->c);

        lexer_advance(lexer);
    }

    return init_token(TOKEN_EOF, "EOF");
}

token_T *lexer_collect_string(lexer_T *lexer)
{
    lexer_advance(lexer);

    char *value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '\0' && lexer->c != '"')
    {
        char *s = lexer_get_current_char_as_string(lexer);

        value = realloc(
            value,
            strlen(value) + strlen(s) + 1
        );

        strcat(value, s);

        lexer_advance(lexer);

        free(s);
    }

    if (lexer->c == '"')
    {
        lexer_advance(lexer);
    }

    return init_token(TOKEN_STRING, value);
}

token_T *lexer_collect_id(lexer_T *lexer)
{
    char *value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '\0' &&
           (isalnum((unsigned char)lexer->c) || lexer->c == '_'))
    {
        char *s = lexer_get_current_char_as_string(lexer);

        value = realloc(
            value,
            strlen(value) + strlen(s) + 1
        );

        strcat(value, s);

        lexer_advance(lexer);

        free(s);
    }

    return init_token(TOKEN_ID, value);
}

token_T *lexer_advance_with_token(
    lexer_T *lexer,
    token_T *token)
{
    lexer_advance(lexer);
    return token;
}

char *lexer_get_current_char_as_string(lexer_T *lexer)
{
    char *str = calloc(2, sizeof(char));

    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}

token_T* lexer_collect_number(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    int dot_count = 0;

    while(
        lexer->c != '\0' &&
        (isdigit((unsigned char)lexer->c) || lexer->c == '.')
    )
    {
        if(lexer->c == '.')
        {
            dot_count++;

            if(dot_count > 1)
            {
                printf("Lexer Error: Invalid float number\n");
                break;
            }
        }

        char* s = lexer_get_current_char_as_string(lexer);

        value = realloc(
            value,
            strlen(value) + strlen(s) + 1
        );

        strcat(value, s);

        free(s);

        lexer_advance(lexer);
    }

    if(dot_count == 0)
    {
        return init_token(TOKEN_INT, value);
    }

    return init_token(TOKEN_FLOAT, value);
}

token_T* lexer_collect_char(lexer_T* lexer)
{
    lexer_advance(lexer); // skip opening '

    if(lexer->c == '\0')
    {
        printf("Syntax Error: Empty character literal\n");
        exit(1);
    }

    char ch = lexer->c;

    lexer_advance(lexer);

    if(lexer->c != '\'')
    {
        printf(
            "Syntax Error: Character literal can contain only one character\n"
        );
        exit(1);
    }

    lexer_advance(lexer); // skip closing '

    char* value = calloc(2, sizeof(char));
    value[0] = ch;
    value[1] = '\0';

    return init_token(TOKEN_CHAR, value);
}

void lexer_skip_comment(lexer_T* lexer)
{
    while(lexer->c != '\0' && lexer->c != '\n')
    {
        lexer_advance(lexer);
    }
}

void lexer_skip_multiline_comment(lexer_T* lexer)
{
    lexer_advance(lexer); // first @
    lexer_advance(lexer); // second @

    while(lexer->c != '\0')
    {
        if(
            lexer->c == '@' &&
            lexer->contents[lexer->i + 1] == '@'
        )
        {
            lexer_advance(lexer);
            lexer_advance(lexer);
            break;
        }

        lexer_advance(lexer);
    }
}