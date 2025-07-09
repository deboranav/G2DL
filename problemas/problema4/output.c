#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c() {
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) { return atof(buffer); }
    return 0.0;
}

void saudacao() {
    printf("Olá, mundo!\n");
    }


int main() {
    // Variáveis globais e escalares inferidas pelo tradutor

    saudacao();
    return 0;
}
