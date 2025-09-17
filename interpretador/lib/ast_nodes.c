#include "ast_nodes.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>

ASTNode *create_var_node(NodeType node_type, char *type, char *name,
                         double *value) {
  ASTNode *node = malloc(sizeof(ASTNode));
  VarNode *vn = malloc(sizeof(VarNode));

  node->type = node_type;
  node->data = vn;

  if (name != NULL) {
    vn->name = malloc(strlen(name) + 1);
    strcpy(vn->name, name);
  } else {
    vn->name = NULL;
  }

  if (type != NULL) {
    vn->type = malloc(strlen(type) + 1);
    strcpy(vn->type, type);
  } else {
    vn->type = NULL;
  }

  if (value != NULL) {
    vn->value = malloc(sizeof(double));
    memcpy(vn->value, value, sizeof(double));
  } else {
    vn->value = NULL;
  }

  return node;
}

void free_var_node(ASTNode *node) {
  VarNode *vn = node->data;

  if (vn->name)
    free(vn->name);
  if (vn->type)
    free(vn->type);
  if (vn->value)
    free(vn->value);

  free(vn);
  free(node);
}