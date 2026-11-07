#include <stdio.h>
#include <string.h>
#include "reto.h"

int calcular(const int muestras[], int m, int tipo, int p, int *estado)
{
    int score = 0;
    int i, error;

    *estado = 1;
    for (i = 0; i < m; i++) {
        error = muestras[i] - p;
        if (error < 0)  {
            error = -error;

        }
        score += (tipo == 0) ? error : error * error;
        if(error > LIMITE_ERROR) {
            *estado = 0;
        }

    }
    return score;
}    

int main(void)
{
    int n, m, q;
    int id, tipo, p;
    char etiqueta[64];
    int muestras[MAX_MUESTRAS];
    int i, score, estado;

    scanf("%d %d %d", &n, &m, &q);
    scanf("%d %63s %d %d", &id, etiqueta, &tipo, &p);
    for (i = 0; i < m; i++) {
        scanf("%d", &muestras[i]);
    }
    score = calcular(muestras, m, tipo, p, &estado);
    printf("%d %d %d\n", id, score, estado);
    return 0;
}
    