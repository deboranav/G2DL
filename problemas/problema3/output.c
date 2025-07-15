/* Analise semantica iniciada... */
/* Analise semantica concluida. */
/* Tradução para C iniciada */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }

int main() {
    double A[2][2];
    double B[2][2];
    double SomaAB[2][2];
    double ProdAB[2][2];
    double C[3][2];
    double D[2][3];
    double ProdCD[3][3];
    double rowsA = 2;
    double colsA = 2;
    double rowsB = 2;
    double colsB = 2;
    double rowsC = 3;
    double colsC = 2;
    double rowsD = 2;
    double colsD = 3;
    printf("--- Teste Estatico de Operacoes com Matrizes ---\n");
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;
    B[0][0] = 5;
    B[0][1] = 6;
    B[1][0] = 7;
    B[1][1] = 8;
    C[0][0] = 1;
    C[0][1] = 2;
    C[1][0] = 3;
    C[1][1] = 4;
    C[2][0] = 5;
    C[2][1] = 6;
    D[0][0] = 1;
    D[0][1] = 0;
    D[0][2] = 2;
    D[1][0] = 0;
    D[1][1] = 3;
    D[1][2] = 1;
    printf("\n--- Teste 1: Matrizes A[2,2] e B[2,2] ---\n");
    printf("Calculando Soma (A + B)...\n");
    SomaAB[0][0] = (A[0][0] + B[0][0]);
    SomaAB[0][1] = (A[0][1] + B[0][1]);
    SomaAB[1][0] = (A[1][0] + B[1][0]);
    SomaAB[1][1] = (A[1][1] + B[1][1]);
    printf("Resultado da Soma:\n");
    printf("[ %.0f, %.0f ]\n", SomaAB[0][0], SomaAB[0][1]);
    printf("[ %.0f, %.0f ]\n", SomaAB[1][0], SomaAB[1][1]);
    printf("Calculando Produto (A * B)...\n");
    ProdAB[0][0] = ((A[0][0] * B[0][0]) + (A[0][1] * B[1][0]));
    ProdAB[0][1] = ((A[0][0] * B[0][1]) + (A[0][1] * B[1][1]));
    ProdAB[1][0] = ((A[1][0] * B[0][0]) + (A[1][1] * B[1][0]));
    ProdAB[1][1] = ((A[1][0] * B[0][1]) + (A[1][1] * B[1][1]));
    printf("Resultado do Produto:\n");
    printf("[ %.0f, %.0f ]\n", ProdAB[0][0], ProdAB[0][1]);
    printf("[ %.0f, %.0f ]\n", ProdAB[1][0], ProdAB[1][1]);
    printf("\n--- Teste 2: Matrizes C[3,2] e D[2,3] ---\n");
    printf("\nVerificando Soma (C + D)...\n");
    if (((rowsC == rowsD) && (colsC == colsD))) {
        printf("A soma é possível.\n");

    } else {
        printf("IMPOSSÍVEL SOMAR: As matrizes precisam ter as mesmas dimensões (C é 3x2, D é 2x3).\n");

    }
    printf("\nVerificando Produto (C * D)...\n");
    if ((colsC == rowsD)) {
        printf("O produto é possível. Calculando...\n");
        ProdCD[0][0] = ((C[0][0] * D[0][0]) + (C[0][1] * D[1][0]));
        ProdCD[0][1] = ((C[0][0] * D[0][1]) + (C[0][1] * D[1][1]));
        ProdCD[0][2] = ((C[0][0] * D[0][2]) + (C[0][1] * D[1][2]));
        ProdCD[1][0] = ((C[1][0] * D[0][0]) + (C[1][1] * D[1][0]));
        ProdCD[1][1] = ((C[1][0] * D[0][1]) + (C[1][1] * D[1][1]));
        ProdCD[1][2] = ((C[1][0] * D[0][2]) + (C[1][1] * D[1][2]));
        ProdCD[2][0] = ((C[2][0] * D[0][0]) + (C[2][1] * D[1][0]));
        ProdCD[2][1] = ((C[2][0] * D[0][1]) + (C[2][1] * D[1][1]));
        ProdCD[2][2] = ((C[2][0] * D[0][2]) + (C[2][1] * D[1][2]));
        printf("Resultado do Produto (matriz 3x3):\n");
        printf("[ %.0f, %.0f, %.0f ]\n", ProdCD[0][0], ProdCD[0][1], ProdCD[0][2]);
        printf("[ %.0f, %.0f, %.0f ]\n", ProdCD[1][0], ProdCD[1][1], ProdCD[1][2]);
        printf("[ %.0f, %.0f, %.0f ]\n", ProdCD[2][0], ProdCD[2][1], ProdCD[2][2]);

    } else {
        printf("IMPOSSIVEL MULTIPLICAR.\n");

    }
    printf("\n--- Fim dos Testes ---\n");

    return 0;
}
/* Tradução concluída com sucesso. */
