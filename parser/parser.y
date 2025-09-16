%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUM 
%token PLUS MINUS TIMES DIVIDE LPAREN RPAREN
%token MOD /* token para calcular o resto*/
%token INCR DECR /* Operadores unarios*/
%token EXIT

/* Precedência e associatividade */
%left PLUS MINUS
%left TIMES DIVIDE MOD
%right UMINUS   /* ex: -5 */
%right POWER     /* associatividade a direita  */
%right INCR DECR   /* ++ e -- associativos a direita */


%%

input:
      /* vazio */
    | input expr '\n'     { printf("= %d\n", $2); }
    | input EXIT '\n'     { printf("Saindo...\n"); exit(0); }
    ;


expr:
      NUM                     { $$ = $1; }
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
                                  if ($3 == 0) {
                                      printf("Erro: módulo por zero\n");
                                      $$ = 0;
                                  } else {
                                      $$ = $1 % $3;
                                  }
                               }
    | LPAREN expr RPAREN      { $$ = $2; }
    | MINUS expr %prec UMINUS { $$ = -$2; }
    | INCR expr               { $$ = $2 + 1; }   /* ++x */
    | DECR expr               { $$ = $2 - 1; }   /* --x */
    | expr INCR               { $$ = $1 + 1; }   /* x++ */
    | expr DECR               { $$ = $1 - 1; }   /* x-- */
    ;
%%

int main() {
    printf("Digite expressões matemáticas (digite 'exit' para sair):\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
    return;
}