#ifndef OPERATOR_UTILS_H
#define OPERATOR_UTILS_H

#include "../include/AST.h"

double operator_get_number(AST_T* node);

AST_T* operator_create_number(
    double value,
    int is_float
);

int operator_result_is_float(
    AST_T* left,
    AST_T* right
);

#endif