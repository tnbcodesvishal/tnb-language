#ifndef ASSIGNMENTS_H
#define ASSIGNMENTS_H

#include "../include/AST.h"
#include "../include/visitor.h"

AST_T* assignment_plus_equal(
    visitor_T* visitor,
    AST_T* vardef,
    AST_T* value
);

#endif