# Exemplo simplificado de Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
# Adiciona todos os diretórios que contêm arquivos .h para a busca do compilador
# O -I. é para o diretório raiz do src e include
INCLUDE_DIRS = -I. -I./src/ast -I./src/lexer -I./src/parser -I./src/interpreter -I./src/utils -I./include

# Lista todos os arquivos .c em subdiretórios
SRC_FILES = $(wildcard src/ast/*.c) \
            $(wildcard src/lexer/*.c) \
            $(wildcard src/parser/*.c) \
            $(wildcard src/interpreter/*.c) \
            $(wildcard src/utils/*.c) \
            src/main.c

# Gera os arquivos .o no diretório build/
OBJ_FILES = $(patsubst src/%.c,build/%.o,$(SRC_FILES))

EXECUTABLE = build/my_interpreter

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c
	@mkdir -p $(@D) # Cria o diretório 'build/subpasta' se não existir
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -rf build/