#ifndef AST_RULES_H
#define AST_RULES_H

#include "ast.h"
#include "ast_nodes.h"
#include <stdbool.h>

bool exec_var_decl(VarNode *node);
bool exec_var_init(VarNode *node);
bool exec_var_update(VarNode *node);

#endif