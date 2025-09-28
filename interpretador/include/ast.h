#ifndef AST_H
#define AST_H

#include <stdbool.h>

typedef enum {
  VAR_DECL,
  VAR_INIT,
  VAR_UPDATE,
  VAR_PRINT,
  EXPR_NUM,
  EXPR_CHAR,
  EXPR_VAR,
  EXPR_PLUS,
  EXPR_MINUS,
  EXPR_TIMES,
  EXPR_DIV,
  EXPR_MOD,
  EXPR_PAR,
  EXPR_NEG,
  EXPR_INC_PREV,
  EXPR_INC_POST,
  EXPR_DEC_PREV,
  EXPR_DEC_POST,
  NODE_LIST,
  NODE_WHILE,
  NODE_DO_WHILE,
} NodeType;

typedef struct {
  NodeType type;
  void *data;
} ASTNode;

extern double exec_node(ASTNode *node);
extern void free_node(ASTNode *node);

#endif