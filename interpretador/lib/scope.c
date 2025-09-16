#include "scope.h"
#include "var.h"
#include <stdio.h>
#include <stdlib.h>

Scope *current_scope = NULL;

void stack_scope() {
  if (current_scope == NULL) {
    current_scope = malloc(sizeof(Scope));
    current_scope->var_list = create_var_list();
    current_scope->bottom = NULL;
  } else {
    Scope *top = malloc(sizeof(Scope));
    top->var_list = create_var_list();
    top->bottom = current_scope;
    current_scope = top;
  }
}

void pop_scope() {
  if (current_scope == NULL) {
    fprintf(stderr, "[DEBUG] Alguma regra apagou o escopo global\n");
    exit(1);
  }

  Scope *top = current_scope;
  current_scope = top->bottom;

  purge_var_list(top->var_list);
  free(top);
}