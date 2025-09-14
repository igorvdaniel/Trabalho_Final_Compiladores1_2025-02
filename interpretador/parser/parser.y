%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "var.h"
#include "rules_var.h"
int yylex(void);
void yyerror(const char *s);
%}

/* Define valor semântico (intValue) */
%union {
    char *strValue;
    double doubleValue;
}

%token <doubleValue> NUM CHAR
%token <strValue> VAR_NAME VAR_TYPE
%token SEMI ";" EQUAL "="

%type <doubleValue> value

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
              printf("[DEBUG] Variavel: %s\n", var->name);
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
                printf("[DEBUG] Variavel inválida\n");
                break;
              }
           } 
         }
       | var_decl
       ;

var_decl: VAR_TYPE[type] VAR_NAME[name] ";" {
            printf("[DEBUG] Declaração de variável: %s\n", $name);
            decl_var($type, $name);
		      }
        | VAR_TYPE[type] VAR_NAME[name] "=" value ";" {
            printf("[DEBUG] Inicializacão de variável: %s\n", $2);
            init_var($type, $name, $value);
          }
        ;

value : CHAR { $$ = $1; }
      | NUM  { $$ = $1; }
      ;

%%

int main(void) {
  create_var_list();
  return yyparse();
}

void yyerror(const char *s) {
  fprintf(stderr, "Erro sintático: %s\n", s);
}
