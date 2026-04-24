#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>

#define REPETITIONS 2
#define TAM 256000
#define MAX_NUM 128000
#define ORDENAR 0
#define CREAR 1
#define INSERTAR 2
#define N 10

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;