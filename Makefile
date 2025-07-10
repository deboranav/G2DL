CC = gcc
LEX = flex
YACC = bison

# Define o diretório de destino e o nome do executável
BIN_DIR = problemas
TARGET = $(BIN_DIR)/compiler_g2dl

LIBS = -lm

# Arquivos fonte
L_FILE = lexg2dl_tokens.l
Y_FILE = parser_g2dl.y
L_C_FILE = $(L_FILE:.l=.yy.c)
Y_C_FILE = $(Y_FILE:.y=.tab.c)
Y_H_FILE = $(Y_FILE:.y=.tab.h)
EXTRA_SRC = lib/symbol_table.c lib/ast.c lib/codegen.c

# Regra principal
all: $(TARGET)

# Regra para criar o executável final dentro da pasta 'problemas'
$(TARGET): $(L_C_FILE) $(Y_C_FILE) $(Y_H_FILE) $(EXTRA_SRC)
	@mkdir -p $(BIN_DIR) # Garante que o diretório exista
	$(CC) $(Y_C_FILE) $(L_C_FILE) $(EXTRA_SRC) -o $(TARGET) $(LIBS)
	@echo "Compilador '$(TARGET)' criado com sucesso."

$(L_C_FILE): $(L_FILE) $(Y_H_FILE)
	$(LEX) -o $(L_C_FILE) $(L_FILE)

$(Y_C_FILE) $(Y_H_FILE): $(Y_FILE)
	$(YACC) -d -Wcounterexamples -o $(Y_C_FILE) $(Y_FILE)

clean:
	rm -f $(TARGET) $(L_C_FILE) $(Y_C_FILE) $(Y_H_FILE)