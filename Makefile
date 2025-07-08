CC = gcc
LEX = flex
YACC = bison
TARGET = compiler_g2dl

LIBS = -lm

L_FILE = lexg2dl_tokens.l
Y_FILE = parser_g2dl.y
L_C_FILE = $(L_FILE:.l=.yy.c)
Y_C_FILE = $(Y_FILE:.y=.tab.c)
Y_H_FILE = $(Y_FILE:.y=.tab.h)
EXTRA_SRC = symbol_table.c

all: $(TARGET)

$(TARGET): $(L_C_FILE) $(Y_C_FILE) $(Y_H_FILE) $(EXTRA_SRC)
	$(CC) $(Y_C_FILE) $(L_C_FILE) $(EXTRA_SRC) -o $(TARGET) $(LIBS)

$(L_C_FILE): $(L_FILE) $(Y_H_FILE)
	$(LEX) -o $(L_C_FILE) $(L_FILE)

$(Y_C_FILE) $(Y_H_FILE): $(Y_FILE)
	$(YACC) -d -Wcounterexamples -o $(Y_C_FILE) $(Y_FILE)

clean:
	rm -f $(TARGET) $(L_C_FILE) $(Y_C_FILE) $(Y_H_FILE)
