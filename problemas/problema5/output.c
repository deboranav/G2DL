#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }

double mdc(double n, double m) {
    if ((((int)m % (int)n) == 0)) {
    return n;
    }
    if ((((int)n % (int)m) == 0)) {
    return m;
    }
    if ((n > m)) {
    return mdc(m, ((int)n % (int)m));
    }
 else {
    return mdc(n, ((int)m % (int)n));
    }
    }


int main() {
    printf("--- Calculo do Maior Divisor Comum (MDC) ---\n");
    double num1;
    double num2;
    double resultado;
    printf("Digite o primeiro numero natural: ");
    num1 = runtime_input_c();
    printf("Digite o segundo numero natural: ");
    num2 = runtime_input_c();
    if (((num1 <= 0) || (num2 <= 0))) {
    printf("Erro: Os numeros devem ser positivos.\n");
    }
 else {
    resultado = mdc(num1, num2);
    printf("O Maior Divisor Comum entre %.0f e %.0f e: %.0f\n", num1, num2, resultado);
    }
    printf("\n--- Fim do Programa ---\n");

    return 0;
}
