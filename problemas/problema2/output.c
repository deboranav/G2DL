/* Analise semantica iniciada... */
/* Analise semantica concluida. */
/* Tradução para C iniciada */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }

int main() {
    double count0_25 = 0.000000;
    double count26_50 = 0.000000;
    double count51_75 = 0.000000;
    double count76_100 = 0.000000;
    printf("Digite um numero (um numero negativo encerra): ");
    double num = runtime_input_c();
    while ((num >= 0.000000)) {
        if (((num >= 0.000000) && (num <= 25.000000))) {
            count0_25 = (count0_25 + 1.000000);

        } else         if (((num >= 26.000000) && (num <= 50.000000))) {
            count26_50 = (count26_50 + 1.000000);

        } else         if (((num >= 51.000000) && (num <= 75.000000))) {
            count51_75 = (count51_75 + 1.000000);

        } else         if (((num >= 76.000000) && (num <= 100.000000))) {
            count76_100 = (count76_100 + 1.000000);

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
/* Tradução concluída com sucesso. */
