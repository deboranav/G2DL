flex lexg2dl.l
yacc -d lexg2dl.y
cc lex.yy.c y.tab.c -o parser.exe 