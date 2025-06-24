CC = gcc
LEX = flex
YACC = bison
TARGET = meu_compilador
L_FILE = lexg2dl_tokens.l
Y_FILE = parser_g2dl.y
L_C_FILE = $(L_FILE:.l=.yy.c)
Y_C_FILE = $(Y_FILE:.y=.tab.c)
Y_H_FILE = $(Y_FILE:.y=.tab.h)

all: $(TARGET)

$(TARGET): $(L_C_FILE) $(Y_C_FILE) $(Y_H_FILE)
	$(CC) $(Y_C_FILE) $(L_C_FILE) -o $(TARGET)

$(L_C_FILE): $(L_FILE) $(Y_H_FILE)
	$(LEX) -o $(L_C_FILE) $(L_FILE)

$(Y_C_FILE) $(Y_H_FILE): $(Y_FILE)
	$(YACC) -d -o $(Y_C_FILE) $(Y_FILE)

clean:
	rm -f $(TARGET) $(L_C_FILE) $(Y_C_FILE) $(Y_H_FILE)