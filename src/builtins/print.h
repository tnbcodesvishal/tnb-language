#ifndef PRINT_H
#define PRINT_H

#include "../include/AST.h"
#include "../include/visitor.h"

AST_T* builtin_function_print(
    visitor_T* visitor,
    AST_T** args,
    int args_size
);

#endif