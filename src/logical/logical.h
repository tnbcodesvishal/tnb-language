#ifndef LOGICAL_H
#define LOGICAL_H

#include "../include/AST.h"
#include "../include/visitor.h"

AST_T* logical_and(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
);

AST_T* logical_or(
    visitor_T* visitor,
    AST_T* left,
    AST_T* right
);

AST_T* logical_not(
    visitor_T* visitor,
    AST_T* value
);

#endif