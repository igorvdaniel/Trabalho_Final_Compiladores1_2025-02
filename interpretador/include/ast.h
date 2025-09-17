#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef enum {
  VAR_DECL,
  VAR_INIT,
  VAR_UPDATE,
} NodeType;

typedef struct {
  NodeType type;
  void *data;
} ASTNode;

typedef struct list {
  ASTNode *node;
  struct list *next;
} ASTList;

void exec_node(ASTNode *node);

#endif