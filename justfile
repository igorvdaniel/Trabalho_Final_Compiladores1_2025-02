parser := "build/parser.tab.c"
lexer := "build/lex.yy.c"
lib := "interpretador/lib/var.c"

build:
    bison -d interpretador/parser/parser.y -o {{parser}}
    flex -o {{lexer}} interpretador/lexer/lexer.l
    gcc -o build/compilador {{parser}} {{lexer}} {{lib}} -lfl -I"interpretador/lib"

run:
    ./build/compilador
