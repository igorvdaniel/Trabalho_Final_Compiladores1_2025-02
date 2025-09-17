#include "ast.h"
#include "ast_nodes.h"
#include "ast_rules.h"
#include "meta.h"
#include <stdio.h>
#include <stdlib.h>

void exec_node(ASTNode *node) {
  switch (node->type) {
  case VAR_DECL:
    VarNode *nvd = node->data;
    if (exec_var_decl(nvd)) {
      printf("[DEBUG] Declaração de variável: %s\n", nvd->name);
    } else {
      fprintf(stderr, "[ERRO] Redeclaração da variável %s na linha %d\n",
              nvd->name, line);
      exit(1);
    }
    free_var_node(node);
    break;
  case VAR_INIT:
    VarNode *nvi = node->data;
    if (exec_var_init(nvi)) {
      printf("[DEBUG] Inicializando a variável: %s\n", nvi->name);
    } else {
      fprintf(stderr, "[ERRO] Redeclaração da variável %s na linha %d\n",
              nvi->name, line);
      exit(1);
    }
    free_var_node(node);
    break;
  case VAR_UPDATE:
    VarNode *nvu = node->data;
    if (exec_var_update(nvu)) {
      printf("[DEBUG] Atualizando valor da variável: %s\n", nvu->name);
    } else {
      fprintf(stderr, "[ERRO] Uso de variável desconhecida %s na linha %d\n",
              nvu->name, line);
      exit(1);
    }
    free_var_node(node);
    break;
  }
}