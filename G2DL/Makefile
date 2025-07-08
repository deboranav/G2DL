# Makefile para o projeto do Interpretador G2DL

# Diretórios
SRCDIR := src
BUILDDIR := build
BINDIR := bin
INCLUDEDIR := include

# Subdiretórios dos módulos
ASTDIR := $(SRCDIR)/ast
LEXERDIR := $(SRCDIR)/lexer
PARSERDIR := $(SRCDIR)/parser
INTERPRETERDIR := $(SRCDIR)/interpreter
UTILSDIR := $(SRCDIR)/utils

# Compilador C
CC := gcc

# Flags de Compilação
# -g: Inclui informações de depuração
# -Wall: Habilita todos os avisos
# -I: Adiciona diretórios para busca de includes
# -std=c11: Usa o padrão C11
# -fPIC: Necessário para criar bibliotecas compartilhadas (opcional, mas boa prática)
# -D_GNU_SOURCE: Pode ser necessário para algumas funções POSIX (ex: strdup)
CFLAGS := -g -Wall -I$(SRCDIR) -I$(ASTDIR) -I$(LEXERDIR) -I$(PARSERDIR) -I$(INTERPRETERDIR) -I$(UTILSDIR) -I$(INTERPRETERDIR) -std=c11 -fPIC -D_GNU_SOURCE

# Flags do Bison
BISONFLAGS := -d -v -t --output=$(PARSERDIR)/parser.tab.c --defines=$(PARSERDIR)/parser.tab.h

# Flags do Flex
FLEXFLAGS := --outfile=$(LEXERDIR)/lexer.yy.c

# Arquivos fonte
C_SOURCES := $(SRCDIR)/main.c \
             $(ASTDIR)/ast.c \
             $(INTERPRETERDIR)/interpreter.c \
             $(INTERPRETERDIR)/symbol_table.c \
             $(UTILSDIR)/types.c \
             $(UTILSDIR)/memory.c \
             $(UTILSDIR)/errors.c \
             $(PARSERDIR)/parser.tab.c \
             $(LEXERDIR)/lexer.yy.c

# Arquivos objeto
# Pega todos os arquivos .c e os transforma em .o na pasta BUILDDIR
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(filter $(SRCDIR)/%.c, $(C_SOURCES)))

# Nome do executável
TARGET := $(BINDIR)/g2dl_interpreter

.PHONY: all clean debug

all: directories $(TARGET)

# Cria os diretórios necessários
directories:
	@mkdir -p $(BUILDDIR) $(BINDIR) $(BUILDDIR)/ast $(BUILDDIR)/lexer $(BUILDDIR)/parser $(BUILDDIR)/interpreter $(BUILDDIR)/utils

# Regra principal para construir o executável
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) -o $@ -lm # -lm para linkar com a biblioteca matemática (sqrt, pow, etc.)
	@echo "Build complete!"

# Regra para gerar os arquivos do parser (.tab.c e .tab.h)
$(PARSERDIR)/parser.tab.c $(PARSERDIR)/parser.tab.h: $(PARSERDIR)/parser.y
	@echo "Generating parser files from $<..."
	bison $(BISONFLAGS) $<

# Regra para gerar o arquivo do lexer (.yy.c)
$(LEXERDIR)/lexer.yy.c: $(LEXERDIR)/lexer.l
	@echo "Generating lexer file from $<..."
	flex $(FLEXFLAGS) $<

# Regra genérica para compilar arquivos .c em .o
# Coloca os arquivos .o nos seus respectivos subdiretórios dentro de BUILDDIR
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regra específica para compilar o parser.tab.c
$(BUILDDIR)/parser/parser.tab.o: $(PARSERDIR)/parser.tab.c
	@echo "Compiling parser.tab.c..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regra específica para compilar o lexer.yy.c
$(BUILDDIR)/lexer/lexer.yy.o: $(LEXERDIR)/lexer.yy.c
	@echo "Compiling lexer.yy.c..."
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa todos os arquivos gerados
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILDDIR) $(BINDIR)
	@rm -f $(PARSERDIR)/parser.tab.c $(PARSERDIR)/parser.tab.h $(LEXERDIR)/lexer.yy.c $(PARSERDIR)/parser.output
	@echo "Clean complete!"

# Ajuda para uso
help:
	@echo "Usage:"
	@echo "  make all    - Builds the interpreter"
	@echo "  make clean  - Removes all generated files"
	@echo "  make debug  - Rebuilds with debugging symbols (default)"
	@echo "  make help   - Displays this help message"