/*
 * Jorge Mera -> jorge.mera
 * Adrián Novio -> adrian.nvilarino
 * Pablo Araujo -> pablo.araujo
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#define M 17
#define N 10
#define MAX_NUM 64000
#define REPETITIONS 3

void inicializar_semilla()
{
    srand(time(NULL));
}

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v[], int n)
{
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - i;
}

void intercambiar(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void listar_vector(int v[], int n)
{
    int i;
    printf("\n[");
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            printf("%d", v[i]);
        }
        else
        {
            printf(", %d", v[i]);
        }
    }
    printf("]\n");
}

bool esta_ordenado(int v[], int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            return printf("Está ordenado?: 0\n");
        }
    }
    return printf("Está ordenado?: 1\n");
}

void ord_ins(int v[], int n)
{
    int i;
    for (i = 1; i < n; i++)
    {
        int x = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void ord_rap_aux(int v[], int izq, int der)
{
    int x, pivote, i = 0, j = 0;
    if (izq < der)
    {
        x = rand() % (der - izq + 1) + izq;
        pivote = v[x];
        intercambiar(&v[izq], &v[x]);
        i = izq + 1;
        j = der;
        while (i <= j)
        {
            while (i <= der && v[i] < pivote)
            {
                i++;
            }
            while (v[j] > pivote)
            {
                j--;
            }
            if (i <= j)
            {
                intercambiar(&v[i], &v[j]);
                i++;
                j--;
            }
        }
        intercambiar(&v[izq], &v[j]);
        ord_rap_aux(v, izq, j - 1);
        ord_rap_aux(v, j + 1, der);
    }
}

void ord_rap(int v[], int n)
{
    ord_rap_aux(v, 0, n - 1);
}

double medirTiempo(void (*algoritmo)(int v[], int tam),
                   void (*f_init)(int v[], int tam), int tam, int k)
{

    double t_test = 0.0;
    double t_test_init = 0.0;
    double t_init = 0.0;
    double t_inicio = 0.0;
    double t_fin = 0.0;

    int i;
    int *v;

    v = malloc(tam * sizeof(int));
    f_init(v, tam);
    t_inicio = microsegundos();
    algoritmo(v, tam);
    t_fin = microsegundos();
    t_test = t_fin - t_inicio;
    if (t_test < 500)
    {
        printf("(*)");
        t_inicio = microsegundos();
        for (i = 0; i < k; i++)
        {
            f_init(v, tam);
            algoritmo(v, tam);
        }
        t_fin = microsegundos();
        t_test_init = t_fin - t_inicio;
        t_inicio = microsegundos();
        for (i = 0; i < k; i++)
        {
            f_init(v, tam);
        }
        t_fin = microsegundos();
        t_init = t_fin - t_inicio;
        t_test = (t_test_init - t_init) / k;
    }
    free(v);
    return t_test;
}

void test_ord()
{
    int v[M];
    int w[N];

    printf("Ordenacion por insercion con inicializacion aleatoria:");
    aleatorio(v, M);
    listar_vector(v, M);
    esta_ordenado(v, M);
    ord_ins(v, M);
    listar_vector(v, M);
    esta_ordenado(v, M);

    printf("\nOrdenacion por insercion con inicializacion ascendente:");
    ascendente(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);
    ord_ins(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);

    printf("\nOrdenacion por insercion con inicializacion descendente:");
    descendente(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);
    ord_ins(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);
}

void test_ord_rap()
{
    int v[M];
    int w[N];

    printf("Ordenacion rapida con inicializacion aleatoria:");
    aleatorio(v, M);
    listar_vector(v, M);
    esta_ordenado(v, M);
    ord_rap(v, M);
    listar_vector(v, M);
    esta_ordenado(v, M);

    printf("\nOrdenacion rapida con inicializacion ascendente:");
    ascendente(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);
    ord_rap(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);

    printf("\nOrdenacion rapida con inicializacion descendente:");
    descendente(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);
    ord_rap(w, M);
    listar_vector(w, M);
    esta_ordenado(w, M);
}

void insercion()
{
    int k = 1000;
    double tiempo = 0.0;
    int n, i;

    for (i = 0; i < REPETITIONS; i++)
    {
        printf("\n\tOrdenacion por insercion con inicializacion descendente:\n");
        printf("\t      n\t\t\t\t t(n)\t\t     t(n)/u(n)\t\t     t(n)/a(n)\t\t"
               "     t(n)/o(n)\n");
        for (n = 500; n <= MAX_NUM; n *= 2)
        {
            tiempo = medirTiempo(ord_ins, descendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.7f\t\t% 14.7f\t\t% 14.7f\n",
                   n, tiempo, tiempo / (pow(n, 1.8)), tiempo / (pow(n, 2)),
                   tiempo / (pow(n, 2.2)));
        }
    }

    for (i = 0; i < REPETITIONS; i++)
    {
        printf("\n\tOrdenacion por insercion con inicializacion ascendente:\n");
        printf("\t      n\t\t\t\t t(n)\t\t     t(n)/u(n)\t\t     t(n)/a(n)\t\t"
               "     t(n)/o(n)\n");
        for (n = 500; n <= MAX_NUM; n *= 2)
        {
            tiempo = medirTiempo(ord_ins, ascendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.7f\t\t% 14.7f\t\t% 14.7f\n",
                   n, tiempo, tiempo / (pow(n, 0.8)), tiempo / n, tiempo / (pow(n, 1.2)));
        }
    }

    for (i = 0; i < REPETITIONS; i++)
    {
        printf("\n\tOrdenacion por insercion con inicializacion aleatoria:\n");
        printf("\t      n\t\t\t\t t(n)\t\t     t(n)/u(n)\t\t     t(n)/a(n)\t\t"
               "     t(n)/o(n)\n");
        for (n = 500; n <= MAX_NUM; n *= 2)
        {
            tiempo = medirTiempo(ord_ins, aleatorio, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.7f\t\t% 14.7f\t\t% 14.7f\n",
                   n, tiempo, tiempo / (pow(n, 1.8)),
                   tiempo / (pow(n, 2)), tiempo / (pow(n, 2.2)));
        }
    }
}

void rapida()
{
    int k = 1000;
    double tiempo = 0.0;
    int n, i;

    for (i = 0; i < REPETITIONS; i++)
    {
        printf("\n\tOrdenacion rapida con inicializacion descendente:\n");
        printf("\t      n\t\t\t\t t(n)\t\t     t(n)/u(n)\t\t     t(n)/a(n)\t\t"
               "     t(n)/o(n)\n");
        for (n = 500; n <= MAX_NUM; n *= 2)
        {
            tiempo = medirTiempo(ord_rap, descendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.7f\t\t% 14.7f\t\t% 14.7f\n",
                   n, tiempo, tiempo / ((n * pow(log2(n), 0.15))),
                   tiempo / ((n * pow(log2(n), 0.45))),
                   tiempo / (n * pow(log2(n), 0.55)));
        }
    }

    for (i = 0; i < REPETITIONS; i++)
    {
        printf("\n\tOrdenacion rapida con inicializacion ascendente:\n");
        printf("\t      n\t\t\t\t t(n)\t\t     t(n)/u(n)\t\t     t(n)/a(n)\t\t"
               "     t(n)/o(n)\n");
        for (n = 500; n <= MAX_NUM; n *= 2)
        {
            tiempo = medirTiempo(ord_rap, ascendente, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.7f\t\t% 14.7f\t\t% 14.7f\n",
                   n, tiempo, tiempo / ((n * pow(log2(n), 0.3))),
                   tiempo / (n * pow(log2(n), 0.6)),
                   tiempo / (n * pow(log2(n), 0.9)));
        }
    }

    for (i = 0; i < REPETITIONS; i++)
    {
        printf("\n\tOrdenacion rapida con inicializacion aleatoria:\n");
        printf("\t      n\t\t\t\t t(n)\t\t     t(n)/u(n)\t\t     t(n)/a(n)\t\t"
               "     t(n)/o(n)\n");
        for (n = 500; n <= MAX_NUM; n *= 2)
        {
            tiempo = medirTiempo(ord_rap, aleatorio, n, k);
            printf("\t% 8d\t\t% 15.4f\t\t% 14.7f\t\t% 14.7f\t\t% 14.7f\n",
                   n, tiempo, tiempo / n, tiempo / (pow(n, 1.1)),
                   tiempo / (pow(n, 1.2)));
        }
    }
}

int main(void)
{
    inicializar_semilla();
    // test_ord();
    // test_ord_rap();
    insercion();
    rapida();

    return 0;
}
