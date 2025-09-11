#ifndef VAR_H
#define VAR_H

#include <stdbool.h>

typedef enum {
  INT,
  FLOAT,
  DOUBLE,
  VAR_CHAR,
  VAR_ENUM_LENGTH, // Usado apenas para obter o comprimento do enum
} VarType;

extern const char *var_type_strings[VAR_ENUM_LENGTH];

typedef struct {
  char *name;
  VarType type;
  void *value;
} Var;

typedef struct VarList {
  Var *var;
  struct VarList *next;
} VarList;

extern void create_var_list();
extern void add_var(VarType type, char *name, void *value);
extern bool update_var(char *name, void *value);
extern Var *get_var(char *name);

#endif
