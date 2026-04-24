#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define MAX_NUM 10000000
#define REPETITIONS 5

double microsegundos() { // obtiene la hora actual en microsegundos
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

int fib1(int n) {
    if (n < 2)
        return n;
    else
        return fib1(n-1) + fib1(n-2);
}

int fib2(int n) {
    int i = 1; int j = 0; int k;

    for (k = 1; k <= n; k++){
        j = i + j;
        i = j - i;
    }

    return j;
}

int fib3(int n) {
    int i, j, k, h, t;
    i = 1; h = 1; j = 0; k = 0; t = 0;

    while (n > 0) {
        if ((n % 2) != 0) {
            t = j * h;
            j = (i * h) + (j * k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2 * k * h) + t;
        k = (k * k) + t;
        n = n / 2;
    }
    return j;
}

void test() {
    int n;
    printf("n\t\t fib1\t\t fib2\t\t fib3\n");
    for (n = 0; n < 21; n++){
        printf("%d\t\t %d\t\t %d\t\t %d \n", n, fib1(n), fib2(n), fib3(n));
    }
}

double medirTiempos(int (*fib)(int), int n, int k) {
    double t_test = 0.0;
    double t_test_init = 0.0;
    double t_init = 0.0;
    double t_inicio = 0.0;
    double t_fin = 0.0;
    int i;

    t_inicio = microsegundos();
    fib(n);
    t_fin = microsegundos();
    t_test = t_fin - t_inicio;

    if (t_test < 500) {
        printf("(*)");
        t_inicio = microsegundos();
        for (i = 0; i < k; i++) {
            fib(n);
        }
        t_fin = microsegundos();
        t_test_init = t_fin - t_inicio;

        t_inicio = microsegundos();
        for (i = 0; i < k; i++);
        t_fin = microsegundos();
        t_init = t_fin - t_inicio;

        t_test = (t_test_init - t_init) / k;
    }

    return t_test;
}

void imprimirTiempos() {
    int k = 1000, n, i;
    double tiempo = 0.0;
    
    for (i = 0; i < REPETITIONS; i++){
        printf("\nMedición de tiempo para fib1:\n");
        printf("\t\tn \t\t\tt(n) \t\tt(n)/(1.1^n)");
        printf("\t\tt(n)/(1+sqrt(5)/2)^n \tt(n)/2^n\n");
        for (n = 2; n <= 32; n *= 2) {
            tiempo = medirTiempos(fib1, n, k);
            printf("\t%8d\t\t%15.4f\t\t%14.10f\t\t%14.12f\t\t%14.12f\n",
                   n, tiempo, tiempo/pow(1.1, n), 
                        tiempo/pow(((1 + sqrt(5))/2), n), tiempo/pow(2, n));
        }
    }
    
    for (i = 0; i < REPETITIONS; i++){
        printf("\nMedición de tiempo para fib2:\n");
        printf("\t\tn \t\t\tt(n) \t\tt(n)/(n^0.8)");
        printf("\t\tt(n)/n \t\t\tt(n)/nlog(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 10) {
            tiempo = medirTiempos(fib2, n, k);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                   n, tiempo, tiempo/pow(n, 0.8), tiempo/n, tiempo/(n * log(n)));
            }
    }
    
    for (i = 0; i < REPETITIONS; i++){
        printf("\nMedición de tiempo para fib3:\n");
        printf("\t\tn \t\t\tt(n) \t\tt(n)/sqrt(log(n))");
        printf("\tt(n)/log(n) \t\tt(n)/n^0.5\n");
        for (n = 1000; n <= MAX_NUM; n *= 10) {
            tiempo = medirTiempos(fib3, n, k);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                   n, tiempo, tiempo/(sqrt(log(n))), tiempo/log(n), 
                        tiempo/pow(n, 0.5));
            }   
    }
}

int main() {
    //test();
    imprimirTiempos();
    return 0;
}
