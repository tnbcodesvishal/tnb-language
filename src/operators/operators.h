#ifndef OPERATORS_H
#define OPERATORS_H

#include "../include/AST.h"
#include "../include/visitor.h"

AST_T* operator_plus(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
);

AST_T* operator_minus(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
);

#endif