%{
#include "parser.tab.h"
%}

%%

[0-9]+          { yylval = atoi(yytext); return NUM; }
"exit"          { return EXIT; } 
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"++"            { return INCR; }
"--"            { return DECR; }
"%"             { return MOD; }
[ \t]+          { /* Ignorar espaços em branco */ }
\n              { return '\n'; }   /* envia a quebra de linha pro parser */
.               { printf("Caractere inválido: %s\n", yytext); }


%%

int yywrap(void) {
    return 1;
}
