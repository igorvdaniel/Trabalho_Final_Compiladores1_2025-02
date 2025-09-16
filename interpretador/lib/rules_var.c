#include "rules_var.h"
#include "scope.h"
#include "var.h"
#include <string.h>

bool decl_var(char *type, char *name) {
  if (strcmp(type, "int") == 0) {
    return add_var(INT, name, NULL);
  }

  else if (strcmp(type, "float") == 0) {
    return add_var(FLOAT, name, NULL);
  }

  else if (strcmp(type, "double") == 0) {
    return add_var(DOUBLE, name, NULL);
  }

  else if (strcmp(type, "char") == 0) {
    return add_var(VAR_CHAR, name, NULL);
  }

  return false;
}

bool init_var(char *type, char *name, double value) {
  if (strcmp(type, "int") == 0) {
    int i = value;
    return add_var(INT, name, &i);
  }

  else if (strcmp(type, "float") == 0) {
    float f = value;
    return add_var(FLOAT, name, &f);
  }

  else if (strcmp(type, "double") == 0) {
    double d = value;
    return add_var(DOUBLE, name, &d);
  }

  else if (strcmp(type, "char") == 0) {
    char c = value;
    return add_var(VAR_CHAR, name, &c);
  }

  return false;
}

bool up_var(char *name, double value) {
  VarList *l = current_scope->var_list;
  Var *var = NULL;

  while (l->var != NULL) {
    if (strcmp(l->var->name, name) == 0) {
      var = l->var;
      break;
    }
    l = l->next;
  }

  if (var != NULL) {
    switch (var->type) {
    case INT:
      int i = value;
      return update_var(INT, var, &i);
      break;
    case FLOAT:
      float f = value;
      return update_var(FLOAT, var, &f);
      break;
    case DOUBLE:
      double d = value;
      return update_var(DOUBLE, var, &d);
      break;
    case VAR_CHAR:
      char c = value;
      return update_var(VAR_CHAR, var, &c);
      break;
    default:
      return false;
      break;
    }
  }

  return false;
}