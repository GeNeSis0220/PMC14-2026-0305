#ifndef RETO_H
#define RETO_H

#define MAX_UNIDADES 20
#define MAX_MUESTRAS 8
#define LONG_NOMBRE 16
#define LIMITE_ERROR 10

typedef struct {
    int tipo;
    int p;

} configuracion;

typedef struct {
    int id;
    char nombre [LONG_NOMBRE];
    configuracion config;
    int score;
    int estado;
} registro; 

int calcular(const int muestras[], int m, int tipo, int p, int *estado);
int total_rec(const registro recs[], int n);
void ordenar(int indices[], const registro recs[], int n);
int buscar(const registro copia[], int n, int q);

#endif

