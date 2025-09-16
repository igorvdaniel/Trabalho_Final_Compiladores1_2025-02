%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "utils.h"
#include "meta.h"
%}

%option always-interactive

N   [0-9]
NSZ [1-9]
AN  [a-zA-Z0-9_]
AL  [_a-zA-Z]

%%

";" { return SEMI; }

"=" { return EQUAL; }

("int"|"float"|"double"|"char") {
    yylval.strValue = strdup(yytext);
    return VAR_TYPE;
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
    yylval.doubleValue = convert_char(yytext);
    return CHAR;
}

[ \t]+    { /* não faz nada */ }

"//".* { /* Comentário */}

\n        { line++; }

.         { printf("Caractere não reconhecido: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
