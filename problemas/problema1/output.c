/* Analise semantica iniciada... */
/* Analise semantica concluida. */
/* Tradução para C iniciada */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }

int main() {
    double x = runtime_input_c();
    double y = runtime_input_c();
    double c = runtime_input_c();
    double d = ((pow(x, 2.000000) - y) + c);
    printf("%f\n", d);

    return 0;
}
/* Tradução concluída com sucesso. */
