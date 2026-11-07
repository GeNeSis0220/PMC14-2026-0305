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

int total_rec(const registro recs[], int n)
{
    if (n == 0) {
        return 0;
    }
    return recs[n - 1].score + total_rec(recs, n - 1);
}

void ordenar(int indices[], const registro recs[], int n)
{
    int i, j, aux, a, b, intercambiar;

    for (i = 0; i < n; i++) {
        indices[i] = i;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            a = indices[j];
            b = indices[j + 1];
            intercambiar = (recs[a].score < recs[b].score) ||
                           (recs[a].score == recs[b].score && recs[a].id > recs[b].id);
            if (intercambiar) {
                aux = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = aux;
            }
        }
    }
}

int buscar(const registro copia[], int n, int q)
{
    int bajo = 0, alto = n - 1, medio;

    while (bajo <= alto) {
        medio = bajo + (alto - bajo) / 2;
        if (copia[medio].id == q) {
            return medio;
        } else if (copia[medio].id < q) {
            bajo = medio + 1;
        } else {
            alto = medio - 1;
        }
    }
    return -1;
}

static int nombre_valido(const char *s)
{
    size_t i, len = strlen(s);

    if (len < 1 || len > LONG_NOMBRE - 1) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = s[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') || c == '_')) {
            return 0;
        }
    }
    return 1;
}

static int leer_entrada(int *n, int *m, int *q, registro recs[],
                        int muestras[][MAX_MUESTRAS])
{
    int i, j, k;
    char etiqueta[64];

    if (scanf("%d %d %d", n, m, q) != 3) return 0;
    if (*n < 1 || *n > MAX_UNIDADES || *m < 1 || *m > MAX_MUESTRAS) return 0;
    if (*q < 1 || *q > 9999) return 0;

    for (i = 0; i < *n; i++) {
        if (scanf("%d %63s %d %d", &recs[i].id, etiqueta,
                  &recs[i].config.tipo, &recs[i].config.p) != 4) return 0;
        if (recs[i].id < 1 || recs[i].id > 9999) return 0;
        if (!nombre_valido(etiqueta)) return 0;
        strcpy(recs[i].nombre, etiqueta);
        if (recs[i].config.tipo != 0 && recs[i].config.tipo != 1) return 0;
        if (recs[i].config.p < 0 || recs[i].config.p > 100) return 0;
        for (k = 0; k < i; k++) {
            if (recs[k].id == recs[i].id) return 0;
        }
        for (j = 0; j < *m; j++) {
            if (scanf("%d", &muestras[i][j]) != 1) return 0;
            if (muestras[i][j] < 0 || muestras[i][j] > 100) return 0;
        }
    }
    return 1;
}

int main(void)
{
    int muestras[MAX_UNIDADES][MAX_MUESTRAS];
    registro recs[MAX_UNIDADES];
    registro copia[MAX_UNIDADES];
    int indices[MAX_UNIDADES];
    int n, m, q, i, pos;

    if (!leer_entrada(&n, &m, &q, recs, muestras)) {
        printf("ERROR\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        recs[i].score = calcular(muestras[i], m, recs[i].config.tipo,
                                 recs[i].config.p, &recs[i].estado);
        printf("%d %d %d\n", recs[i].id, recs[i].score, recs[i].estado);
    }
    printf("TOTAL %d\n", total_rec(recs, n));

    ordenar(indices, recs, n);
    printf("ORDER");
    for (i = 0; i < n; i++) {
        printf(" %d", recs[indices[i]].id);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        int j = i - 1;
        registro actual = recs[i];
        while (j >= 0 && copia[j].id > actual.id) {
            copia[j + 1] = copia[j];
            j--;
        }
        copia[j + 1] = actual;
    }
    pos = buscar(copia, n, q);
    printf("FIND %d %d\n", q, pos >= 0 ? copia[pos].score : -1);
    return 0;
}
    