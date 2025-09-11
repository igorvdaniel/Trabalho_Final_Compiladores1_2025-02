%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "var.h"
int yylex(void);
void yyerror(const char *s);
%}

/* Define valor semântico (intValue) */
%union {
    char charValue;
    char *strValue;
    double doubleValue;
    int intValue;
}

%token <doubleValue> NUM
%token <strValue> VAR_NAME NUM_VAR CHAR_VAR CHAR
%token SEMI ";"
%token EQUAL "="

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

var_decl: NUM_VAR[type] VAR_NAME[name] ";" {
            printf("[DEBUG] Declaração de variável: %s\n", $name);

            if (strcmp($type, "int") == 0) {
              add_var(INT, $name, NULL);
            }

            else if (strcmp($type, "float") == 0) {
              add_var(FLOAT, $name, NULL);
            }

            else if (strcmp($type, "double") == 0) {
              add_var(DOUBLE, $name, NULL);
            }
		      }
        | NUM_VAR[type] VAR_NAME[name] "=" NUM[value] ";" {
            printf("[DEBUG] Inicializacão de variável: %s\n", $2);

            if (strcmp($type, "int") == 0) {
              int i = (int)$value;
              add_var(INT, $name, &i);
            }

            else if (strcmp($type, "float") == 0) {
              float f = (float)$value;
              add_var(FLOAT, $name, &f);
            }

            else if (strcmp($type, "double") == 0) {
              double d = $value;
              add_var(DOUBLE, $name, &d);
            }
          }
        | CHAR_VAR[type] VAR_NAME[name] ";" {
            printf("[DEBUG] Declaração de variável: %s\n", $name);
            add_var(CHAR, $name, NULL);
        }
        | CHAR_VAR[type] VAR_NAME[name] "=" CHAR[value] ";" {
            printf("[DEBUG] Inicialização de variável: %s\n", $name);

            char c;

            if (strlen($value) == 4) {
              switch ($value[2]) {
                case 'n':
                  c = '\n';
                  break;
                case '0':
                  c = '\0';
                  break;
              }
            } else {
              c = $value[1];
            }

            add_var(VAR_CHAR, $name, &c);
        }
        ;

%%

int main(void) {
  create_var_list();
  return yyparse();
}

void yyerror(const char *s) {
  fprintf(stderr, "Erro sintático: %s\n", s);
}
