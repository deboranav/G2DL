## Como gerar compilador de G2DL

### Passo 1:

```bash
$ make clean && make
```
O Make gera um "compiler_g2dl" na pasta "problemas", basta copia-lo para a pasta do problema a ser testado.

### Passo 2:

```bash
$ ./compiler_g2dl probNum.g2dl > output.c
```


### Passo 3:

```bash
$ gcc output.c -o programa_finalNum -lm
```

### Passo 4:

```bash
$ ./programa_final.exe
```

### Passo extra para limpar o compilador:

```bash
$ make clean
```
