#ifndef RULES_VAR_H
#define RULES_VAR_H

#include <stdbool.h>

extern bool decl_var(char *type, char *name);
extern bool init_var(char *type, char *name, double value);
extern bool up_var(char *name, double value);

#endif