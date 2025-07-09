#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c() {
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        return atof(buffer);
    }
    return 0.0;
}

int main() {
    // Variáveis inferidas pelo tradutor
    double count0_25;
    double count26_50;
    double count51_75;
    double count76_100;
    double num;

    count0_25 = 0;
    count26_50 = 0;
    count51_75 = 0;
    count76_100 = 0;
    printf("Digite um numero (um numero negativo encerra): ");
    num = runtime_input_c();
    while ((num >= 0)) {
    if (((num >= 0) && (num <= 25))) {
    count0_25 = (count0_25 + 1);
    }
 else     if (((num >= 26) && (num <= 50))) {
    count26_50 = (count26_50 + 1);
    }
 else     if (((num >= 51) && (num <= 75))) {
    count51_75 = (count51_75 + 1);
    }
 else     if (((num >= 76) && (num <= 100))) {
    count76_100 = (count76_100 + 1);
    }
    printf("Digite um numero (um numero negativo encerra): ");
    num = runtime_input_c();
    }
    printf("Resultados:\n");
    printf("Numeros no intervalo [0, 25]: %.0f\n", count0_25);
    printf("Numeros no intervalo [26, 50]: %.0f\n", count26_50);
    printf("Numeros no intervalo [51, 75]: %.0f\n", count51_75);
    printf("Numeros no intervalo [76, 100]: %.0f\n", count76_100);

    return 0;
}
