    #ifndef COMPARISONS_H
    #define COMPARISONS_H

    #include "../include/AST.h"
    #include "../include/visitor.h"
    #include "comparison_utils.h"

    AST_T* comparison_equal(
        visitor_T* visitor,
        AST_T* left,
        AST_T* right
    );

    AST_T* comparison_not_equal(
        visitor_T* visitor,
        AST_T* left,
        AST_T* right
    );

    AST_T* comparison_greater(
        visitor_T* visitor,
        AST_T* left,
        AST_T* right
    );

    AST_T* comparison_less(
        visitor_T* visitor,
        AST_T* left,
        AST_T* right
    );

    AST_T* comparison_greater_equal(
        visitor_T* visitor,
        AST_T* left,
        AST_T* right
    );

    AST_T* comparison_less_equal(
        visitor_T* visitor,
        AST_T* left,
        AST_T* right
    );
    #endif