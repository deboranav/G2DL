#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct rational_t {
    double numerador;
    double denominador;
};

double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }

struct rational_t cria_racional(double num, double den) {
    struct rational_t novo_r;
    if ((den == 0)) {
    printf("Erro: Denominador não pode ser zero. Retornando 0/1.\n");
    novo_r.numerador = 0;
    novo_r.denominador = 1;
    }
 else {
    novo_r.numerador = num;
    novo_r.denominador = den;
    }
    return novo_r;
    }

double sao_iguais(struct rational_t r1, struct rational_t r2) {
    if (((r1.numerador * r2.denominador) == (r2.numerador * r1.denominador))) {
    return 1.000000;
    }
    return 0.000000;
    }

struct rational_t soma(struct rational_t r1, struct rational_t r2) {
    struct rational_t res_soma;
    res_soma.numerador = ((r1.numerador * r2.denominador) + (r2.numerador * r1.denominador));
    res_soma.denominador = (r1.denominador * r2.denominador);
    return res_soma;
    }

struct rational_t multiplicacao(struct rational_t r1, struct rational_t r2) {
    struct rational_t res_mult;
    res_mult.numerador = (r1.numerador * r2.numerador);
    res_mult.denominador = (r1.denominador * r2.denominador);
    return res_mult;
    }

struct rational_t nega(struct rational_t r) {
    struct rational_t res_nega;
    res_nega.denominador = r.denominador;
    return res_nega;
    }


int main() {
    // Variáveis locais da main (escalares)
    double sao_diferentes;

    printf("--- Testando Subprogramas de Racionais com Funções Tipadas ---\n");
    struct rational_t r1;
    struct rational_t r2;
    struct rational_t r3;
    double sao_diferentes;
    printf("\nCriando racionais r1=3/4 e r2=1/2...\n");
    r1 = cria_racional(3, 4);
    r2 = cria_racional(1, 2);
    printf("r1 = %.0f/%.0f\n", r1.numerador, r1.denominador);
    printf("r2 = %.0f/%.0f\n", r2.numerador, r2.denominador);
    printf("\nTestando igualdade...\n");
    sao_diferentes = sao_iguais(r1, r2);
    if ((sao_diferentes == 1.000000)) {
    printf("r1 e r2 são iguais.\n");
    }
 else {
    printf("r1 e r2 são diferentes.\n");
    }
    printf("\nTestando operações...\n");
    r3 = soma(r1, r2);
    printf("Soma (r1 + r2) = %.0f/%.0f\n", r3.numerador, r3.denominador);
    r3 = multiplicacao(r1, r2);
    printf("Produto (r1 * r2) = %.0f/%.0f\n", r3.numerador, r3.denominador);
    r3 = nega(r1);
    printf("Negação (-r1) = %.0f/%.0f\n", r3.numerador, r3.denominador);
    printf("\n--- Fim do Programa ---\n");

    return 0;
}
