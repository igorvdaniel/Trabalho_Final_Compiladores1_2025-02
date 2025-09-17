#include "var.h"
#include "scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *var_type_strings[] = {
    [INT] = "int",
    [FLOAT] = "float",
    [DOUBLE] = "double",
    [VAR_CHAR] = "char",
};

VarList *create_var_list() {
  VarList *vl = malloc(sizeof(VarList));
  vl->var = NULL;
  vl->next = NULL;

  return vl;
}

void purge_var_list(VarList *v) {
  while (v != NULL) {
    VarList *current = v;
    v = v->next;

    if (current->var) {
      free(current->var->name);
      free(current->var->value);
      free(current->var);
    }

    free(current);
  }
}

Var *get_var(char *name) {
  Scope *scope = current_scope;

  while (scope != NULL) {
    VarList *l = scope->var_list;

    while (l->var != NULL) {
      if (strcmp(l->var->name, name) == 0)
        return l->var;
      l = l->next;
    }

    scope = scope->bottom;
  }

  return NULL;
}

bool add_var(VarType type, char *name, void *value) {
  VarList *l = current_scope->var_list;

  while (l->var != NULL) {
    if (strcmp(l->var->name, name) == 0)
      return false;
    l = l->next;
  }

  l->var = malloc(sizeof(Var));
  l->next = malloc(sizeof(VarList));
  l->next->var = NULL;
  l->next->next = NULL;

  Var *var = l->var;

  var->name = malloc(strlen(name) + 1);
  strcpy(var->name, name);

  var->type = type;

  switch (type) {
  case INT:
    var->value = malloc(sizeof(int));
    if (value != NULL)
      memcpy(var->value, value, sizeof(int));
    break;
  case FLOAT:
    var->value = malloc(sizeof(float));
    if (value != NULL)
      memcpy(var->value, value, sizeof(float));
    break;
  case DOUBLE:
    var->value = malloc(sizeof(double));
    if (value != NULL)
      memcpy(var->value, value, sizeof(double));
    break;
  case VAR_CHAR:
    var->value = malloc(sizeof(char));
    if (value != NULL)
      memcpy(var->value, value, sizeof(char));
    break;
  default:
    break;
  }

  return true;
}

bool update_var(VarType type, Var *var, void *value) {
  if (type <= VAR_CHAR) {
    switch (var->type) {
    case INT:
      memcpy(var->value, value, sizeof(int));
      break;
    case FLOAT:
      memcpy(var->value, value, sizeof(float));
      break;
    case DOUBLE:
      memcpy(var->value, value, sizeof(double));
      break;
    case VAR_CHAR:
      memcpy(var->value, value, sizeof(char));
      break;
    default:
      return false;
      break;
    }

    return true;
  }

  return false;
}
