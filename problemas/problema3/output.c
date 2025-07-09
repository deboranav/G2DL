#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c()
{
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        return atof(buffer);
    }
    return 0.0;
}

int main()
{
    // Variáveis escalares inferidas pelo tradutor
    double rowsA;
    double colsA;
    double rowsB;
    double colsB;
    double rowsC;
    double colsC;
    double rowsD;
    double colsD;

    double A[2][2];
    double B[2][2];
    double SomaAB[2][2];
    double ProdAB[2][2];
    double C[3][2];
    double D[2][3];
    double ProdCD[3][3];
    rowsA = 2;
    colsA = 2;
    rowsB = 2;
    colsB = 2;
    rowsC = 3;
    colsC = 2;
    rowsD = 2;
    colsD = 3;
    printf("--- Teste Estatico de Operacoes com Matrizes ---\n");
    A[(int)(0)][(int)(0)] = 1;
    A[(int)(0)][(int)(1)] = 2;
    A[(int)(1)][(int)(0)] = 3;
    A[(int)(1)][(int)(1)] = 4;
    B[(int)(0)][(int)(0)] = 5;
    B[(int)(0)][(int)(1)] = 6;
    B[(int)(1)][(int)(0)] = 7;
    B[(int)(1)][(int)(1)] = 8;
    C[(int)(0)][(int)(0)] = 1;
    C[(int)(0)][(int)(1)] = 2;
    C[(int)(1)][(int)(0)] = 3;
    C[(int)(1)][(int)(1)] = 4;
    C[(int)(2)][(int)(0)] = 5;
    C[(int)(2)][(int)(1)] = 6;
    D[(int)(0)][(int)(0)] = 1;
    D[(int)(0)][(int)(1)] = 0;
    D[(int)(0)][(int)(2)] = 2;
    D[(int)(1)][(int)(0)] = 0;
    D[(int)(1)][(int)(1)] = 3;
    D[(int)(1)][(int)(2)] = 1;
    printf("\n--- Teste 1: Matrizes A[2,2] e B[2,2] ---\n");
    printf("Calculando Soma (A + B)...\n");
    SomaAB[(int)(0)][(int)(0)] = (A[(int)(0)][(int)(0)] + B[(int)(0)][(int)(0)]);
    SomaAB[(int)(0)][(int)(1)] = (A[(int)(0)][(int)(1)] + B[(int)(0)][(int)(1)]);
    SomaAB[(int)(1)][(int)(0)] = (A[(int)(1)][(int)(0)] + B[(int)(1)][(int)(0)]);
    SomaAB[(int)(1)][(int)(1)] = (A[(int)(1)][(int)(1)] + B[(int)(1)][(int)(1)]);
    printf("Resultado da Soma:\n");
    printf("[ %.0f, %.0f ]\n", SomaAB[(int)(0)][(int)(0)], SomaAB[(int)(0)][(int)(1)]);
    printf("[ %.0f, %.0f ]\n", SomaAB[(int)(1)][(int)(0)], SomaAB[(int)(1)][(int)(1)]);
    printf("Calculando Produto (A * B)...\n");
    ProdAB[(int)(0)][(int)(0)] = ((A[(int)(0)][(int)(0)] * B[(int)(0)][(int)(0)]) + (A[(int)(0)][(int)(1)] * B[(int)(1)][(int)(0)]));
    ProdAB[(int)(0)][(int)(1)] = ((A[(int)(0)][(int)(0)] * B[(int)(0)][(int)(1)]) + (A[(int)(0)][(int)(1)] * B[(int)(1)][(int)(1)]));
    ProdAB[(int)(1)][(int)(0)] = ((A[(int)(1)][(int)(0)] * B[(int)(0)][(int)(0)]) + (A[(int)(1)][(int)(1)] * B[(int)(1)][(int)(0)]));
    ProdAB[(int)(1)][(int)(1)] = ((A[(int)(1)][(int)(0)] * B[(int)(0)][(int)(1)]) + (A[(int)(1)][(int)(1)] * B[(int)(1)][(int)(1)]));
    printf("Resultado do Produto:\n");
    printf("[ %.0f, %.0f ]\n", ProdAB[(int)(0)][(int)(0)], ProdAB[(int)(0)][(int)(1)]);
    printf("[ %.0f, %.0f ]\n", ProdAB[(int)(1)][(int)(0)], ProdAB[(int)(1)][(int)(1)]);
    printf("\n--- Teste 2: Matrizes C[3,2] e D[2,3] ---\n");
    printf("\nVerificando Soma (C + D)...\n");
    if (((rowsC == rowsD) && (colsC == colsD)))
    {
        printf("A soma é possível.\n");
    }
    else
    {
        printf("IMPOSSÍVEL SOMAR: As matrizes precisam ter as mesmas dimensões (C é 3x2, D é 2x3).\n");
    }
    printf("\nVerificando Produto (C * D)...\n");
    if ((colsC == rowsD))
    {
        printf("O produto é possível. Calculando...\n");
        ProdCD[(int)(0)][(int)(0)] = ((C[(int)(0)][(int)(0)] * D[(int)(0)][(int)(0)]) + (C[(int)(0)][(int)(1)] * D[(int)(1)][(int)(0)]));
        ProdCD[(int)(0)][(int)(1)] = ((C[(int)(0)][(int)(0)] * D[(int)(0)][(int)(1)]) + (C[(int)(0)][(int)(1)] * D[(int)(1)][(int)(1)]));
        ProdCD[(int)(0)][(int)(2)] = ((C[(int)(0)][(int)(0)] * D[(int)(0)][(int)(2)]) + (C[(int)(0)][(int)(1)] * D[(int)(1)][(int)(2)]));
        ProdCD[(int)(1)][(int)(0)] = ((C[(int)(1)][(int)(0)] * D[(int)(0)][(int)(0)]) + (C[(int)(1)][(int)(1)] * D[(int)(1)][(int)(0)]));
        ProdCD[(int)(1)][(int)(1)] = ((C[(int)(1)][(int)(0)] * D[(int)(0)][(int)(1)]) + (C[(int)(1)][(int)(1)] * D[(int)(1)][(int)(1)]));
        ProdCD[(int)(1)][(int)(2)] = ((C[(int)(1)][(int)(0)] * D[(int)(0)][(int)(2)]) + (C[(int)(1)][(int)(1)] * D[(int)(1)][(int)(2)]));
        ProdCD[(int)(2)][(int)(0)] = ((C[(int)(2)][(int)(0)] * D[(int)(0)][(int)(0)]) + (C[(int)(2)][(int)(1)] * D[(int)(1)][(int)(0)]));
        ProdCD[(int)(2)][(int)(1)] = ((C[(int)(2)][(int)(0)] * D[(int)(0)][(int)(1)]) + (C[(int)(2)][(int)(1)] * D[(int)(1)][(int)(1)]));
        ProdCD[(int)(2)][(int)(2)] = ((C[(int)(2)][(int)(0)] * D[(int)(0)][(int)(2)]) + (C[(int)(2)][(int)(1)] * D[(int)(1)][(int)(2)]));
        printf("Resultado do Produto (matriz 3x3):\n");
        printf("[ %.0f, %.0f, %.0f ]\n", ProdCD[(int)(0)][(int)(0)], ProdCD[(int)(0)][(int)(1)], ProdCD[(int)(0)][(int)(2)]);
        printf("[ %.0f, %.0f, %.0f ]\n", ProdCD[(int)(1)][(int)(0)], ProdCD[(int)(1)][(int)(1)], ProdCD[(int)(1)][(int)(2)]);
        printf("[ %.0f, %.0f, %.0f ]\n", ProdCD[(int)(2)][(int)(0)], ProdCD[(int)(2)][(int)(1)], ProdCD[(int)(2)][(int)(2)]);
    }
    else
    {
        printf("IMPOSSIVEL MULTIPLICAR.\n");
    }
    printf("\n--- Fim dos Testes ---\n");

    return 0;
}
