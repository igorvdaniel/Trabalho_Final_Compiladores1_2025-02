#include "rules_var.h"
#include "var.h"
#include <string.h>

void decl_var(char *type, char *name) {
  if (strcmp(type, "int") == 0) {
    add_var(INT, name, NULL);
  }

  else if (strcmp(type, "float") == 0) {
    add_var(FLOAT, name, NULL);
  }

  else if (strcmp(type, "double") == 0) {
    add_var(DOUBLE, name, NULL);
  }

  else if (strcmp(type, "char") == 0) {
    add_var(VAR_CHAR, name, NULL);
  }
}

void init_var(char *type, char *name, double value) {
  if (strcmp(type, "int") == 0) {
    int i = (int)value;
    add_var(INT, name, &i);
  }

  else if (strcmp(type, "float") == 0) {
    float f = (float)value;
    add_var(FLOAT, name, &f);
  }

  else if (strcmp(type, "double") == 0) {
    double d = value;
    add_var(DOUBLE, name, &d);
  }

  else if (strcmp(type, "char") == 0) {
    char c = (char)value;
    add_var(VAR_CHAR, name, &c);
  }
}