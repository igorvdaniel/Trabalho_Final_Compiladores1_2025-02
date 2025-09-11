%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
%}

%option always-interactive

N   [0-9]
NSZ [1-9]
AN  [a-zA-Z0-9_]
AL  [_a-zA-Z]

%%

";" { return SEMI; }

"=" { return EQUAL; }

("int"|"float"|"double") {
    yylval.strValue = strdup(yytext);
    return NUM_VAR;
}

"char" {
    yylval.strValue = strdup(yytext);
    return CHAR_VAR;
}

{AL}{AN}* {
    yylval.strValue = strdup(yytext);
    return VAR_NAME;
}

[+-]?{N}+(\.{N}+)?  {
    yylval.doubleValue = atof(yytext);
    return NUM;
}

'(\\)?.' {
    yylval.strValue = strdup(yytext);
    return CHAR;
}

[ \t\n]+  { /* não faz nada */ }

.         { printf("Caractere não reconhecido: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
