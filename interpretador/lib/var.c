#include "var.h"
#include <stdlib.h>
#include <string.h>

VarList *global_vars;

const char *var_type_strings[] = {
    [INT] = "int",
    [FLOAT] = "float",
    [DOUBLE] = "double",
    [VAR_CHAR] = "char",
};

void create_var_list() {
  global_vars = malloc(sizeof(VarList));
  global_vars->var = NULL;
  global_vars->next = NULL;
}

Var *get_var(char *name) {
  VarList *l = global_vars;
  while (l->next != NULL) {
    if (strcmp(l->var->name, name) == 0)
      return l->var;

    l = l->next;
  }

  return NULL;
}

bool add_var(VarType type, char *name, void *value) {
  VarList *l;

  for (l = global_vars; l->var != NULL; l = l->next) {
    if (strcmp(l->var->name, name) == 0)
      return false;
  }

  l->next = malloc(sizeof(VarList));

  Var *var = malloc(sizeof(Var));

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

  l->var = var;
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
