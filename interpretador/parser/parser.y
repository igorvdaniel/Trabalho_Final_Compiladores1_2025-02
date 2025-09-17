%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "ast_nodes.h"
#include "var.h"
#include "scope.h"
#include "meta.h"
int yylex(void);
void yyerror(const char *s);
%}

/* Define valor semântico (intValue) */
%union {
    char *strValue;
    double doubleValue;
    ASTNode *node;
}


%token <doubleValue> NUM CHAR
%token <strValue> VAR_NAME VAR_TYPE
%token SEMI ";" EQUAL "="

%type <doubleValue> expr
%type <node> var_decl var_update

/* Operações */
%token PLUS MINUS TIMES DIVIDE LPAREN RPAREN
%token MOD /* token para calcular o resto*/
%token INCR DECR /* Operadores unarios*/

/* Precedência e associatividade */
%left PLUS MINUS
%left TIMES DIVIDE MOD
%right UMINUS   /* ex: -5 */
%right INCR DECR   /* ++ e -- associativos a direita */

%start input

%%

input: 
     | input program
     ;

program:  VAR_NAME[name] ";" {
            Var *var = get_var($name);
            if (var != NULL) {
              VarType type = var->type;
              void *value = var->value;
              printf("[DEBUG] Variável: %s\n", var->name);
              printf("[DEBUG] Tipo: %s\n", var_type_strings[type]);

              switch (type) {
              case INT:
                int *int_value = value;
                printf("[DEBUG] Valor: %d\n", *int_value);
                break;
              case FLOAT:
                float *float_value = value;
                printf("[DEBUG] Valor: %f\n", *float_value);
                break;
              case DOUBLE:
                double *double_value = value;
                printf("[DEBUG] Valor: %lf\n", *double_value);
                break;
              case VAR_CHAR:
                char *char_value = value;
                printf("[DEBUG] Valor: '%c'\n", *char_value);
                break;
              default:
                printf("[DEBUG] Variável inválida\n");
                break;
              }
           } else {
              fprintf(stderr, 
                      "[ERRO] Uso de variável desconhecida %s na linha %d\n", 
                      $name,
                      line);
              YYABORT;
           }
         }
       | var_decl { exec_node($1); }
       | var_update { exec_node($1); }
       ;

var_decl: VAR_TYPE[type] VAR_NAME[name] ";" {
            $$ = create_var_node(VAR_DECL, $type, $name, NULL);
		      }
        | VAR_TYPE[type] VAR_NAME[name] "=" expr ";" {
            $$ = create_var_node(VAR_INIT, $type, $name, &$expr);
          }
        ;

var_update: VAR_NAME[name] "=" expr ";" {
              $$ = create_var_node(VAR_UPDATE, NULL, $name, &$expr);
            }
          ;

expr:
      NUM                     { $$ = $1; }
    | CHAR                    { $$ = $1; }
    | expr PLUS expr          { $$ = $1 + $3; }
    | expr MINUS expr         { $$ = $1 - $3; }
    | expr TIMES expr         { $$ = $1 * $3; }
    | expr DIVIDE expr        { 
                                  if ($3 == 0) { 
                                      printf("Erro: divisão por zero\n"); 
                                      $$ = 0; 
                                  } else { 
                                      $$ = $1 / $3; 
                                  }
                               }
     | expr MOD expr           {
                                if ($3 == 0 || (long)$1 != $1 || (long) $3 != $3) {
                                  fprintf(stderr, 
                                    "[ERRO] Operação de módulo com 0 na linha %d\n",
                                    line);
                                  exit(0);

                                } else {
                                  $$ = (long)$1 % (long)$3;
                                }
                               }
    | LPAREN expr RPAREN      { $$ = $2; }
    | MINUS expr %prec UMINUS { $$ = -$2; }
    | INCR expr               { $$ = $2 + 1; }   /* ++x */
    | DECR expr               { $$ = $2 - 1; }   /* --x */
    | expr INCR               { $$ = $1 + 1; }   /* x++ */
    | expr DECR               { $$ = $1 - 1; }   /* x-- */
    ;

/*
value : CHAR { $$ = $1; }
      | NUM  { $$ = $1; }
      ;
*/

%%

int main(void) {
  stack_scope();
  int r = yyparse();
  pop_scope();
  return r;
}

void yyerror(const char *s) {
  fprintf(stderr, "[ERRO] Sintaxe inválida na linha %d\n", line);
}
