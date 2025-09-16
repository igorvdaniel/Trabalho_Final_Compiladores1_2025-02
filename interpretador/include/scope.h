#ifndef SCOPE_H
#define SCOPE_H

#include "var.h"

typedef struct scope {
  VarList *var_list;
  struct scope *bottom;
} Scope;

extern Scope *current_scope;

extern void stack_scope();
extern void pop_scope();

#endif