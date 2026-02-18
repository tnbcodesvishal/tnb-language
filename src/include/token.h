#ifndef TOKEN_H
#define TOKEN_H

/* Token types */
typedef enum {
    TOKEN_ID,
    TOKEN_EQUALS,     // =
    TOKEN_STRING,
    TOKEN_SEMI,       // ;
    TOKEN_LPAREN,     // (  
    TOKEN_RPAREN,     // )
    TOKEN_EOF
} type;

/* Token structure */
typedef struct TOKEN_STRUCT {
    type type;
    char *value;
} token_T;

token_T *init_token(int type, char *value);

#endif  /* TOKEN_H */
