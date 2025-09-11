#include "var.h"
#include <stdlib.h>
#include <string.h>

VarList *list;

const char *var_type_strings[] = {
    [INT] = "int",
    [FLOAT] = "float",
    [DOUBLE] = "double",
    [VAR_CHAR] = "char",
};

void create_var_list() {
  list = malloc(sizeof(VarList));
  list->var = NULL;
  list->next = NULL;
}

void add_var(VarType type, char *name, void *value) {
  VarList *l;

  for (l = list; l->var != NULL; l = l->next) {
    if (strcmp(l->var->name, name) == 0)
      return;
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
}

Var *get_var(char *name) {
  VarList *l = list;
  while (l->next != NULL) {
    if (strcmp(l->var->name, name) == 0)
      return l->var;

    l = l->next;
  }

  return NULL;
}
