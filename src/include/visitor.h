#ifndef VISITOR_H
#define VISITOR_H
#include "AST.h"

typedef struct VISITOR_STRUCT
{
     AST_T** variables_definations;
     size_t variables_definations_size;
}visitor_T;

visitor_T* init_visitor();

AST_T* visitor_visit(visitor_T* visitor, AST_T* node);  

AST_T* visitor_visit_variable_defination(visitor_T* visitor, AST_T* node);

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node);

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node);

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node);

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node);

AST_T* visitor_visit_int(visitor_T* visitor, AST_T* node);

AST_T* visitor_visit_float(visitor_T* visitor, AST_T* node);
AST_T* visitor_visit_char(visitor_T* visitor,AST_T* node);

AST_T* visitor_visit_binop( visitor_T* visitor,AST_T* node);
AST_T* visitor_visit_unary( visitor_T* visitor,AST_T* node);





#endif
