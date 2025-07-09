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
    // Variáveis escalares inferidas pelo tradutor
    double x;
    double y;
    double c;
    double d;

    x = 3.500000;
    y = 1.200000;
    c = 4;
    d = ((pow(x, 2) - y) + c);
    printf("%f\n", d);

    return 0;
}
