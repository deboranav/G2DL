flex lexg2dl_tokens.l
bison -d parser_g2dl.y
gcc lex.yy.c parser_g2dl.tab.c symbol_table.c -o compiler_g2dl.exe