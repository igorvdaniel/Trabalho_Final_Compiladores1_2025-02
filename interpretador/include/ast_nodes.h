#ifndef AST_NODES_H
#define AST_NODES_H

#include "ast.h"

typedef struct {
  char *type;
  char *name;
  double *value;
} VarNode;

ASTNode *create_var_node(NodeType node_type, char *type, char *name,
                         double *value);
void free_var_node(ASTNode *node);

#endif