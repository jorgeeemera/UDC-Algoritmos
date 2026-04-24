/*
Alumno 1: Adrián Novio Vilariño
Alumno 2: Pablo Araújo Rodríguez
Alumno 3: Jorge Mera Hermida 
*/

#include "monticulo.h"

void inicializar_semilla() {
    srand(time(NULL));
}

void intercambiar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

bool estaOrdenado(int v[], int n){
    int i;
    for (i = 0; i < n - 1; i++){
        if (v[i] > v[i + 1]){
            return printf("Está ordenado?: 0\n\n"); 
        }
    }
    return printf("Está ordenado?: 1\n\n");
}

void aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v [], int n) {
    int i;
    for (i = 0; i < n; i++){
        v[i] = i + 1;
    }
}

void descendente(int v [], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void listar_vector(int v[], int n) {
    int i;
    printf("\n[");
    for (i = 0; i < n; i++) {
        if (i == 0){
            printf("%d", v[i]);
        } else {
            printf(", %d", v[i]);
        }
    }
    printf("]\n");
}

void iniMonticulo(pmonticulo m) {
    m -> ultimo = -1;
}

void hundir(pmonticulo m, int i) {
    int min = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq <= m -> ultimo && m -> vector[izq] < m -> vector[min]) {
        min = izq;
    }
    if (der <= m -> ultimo && m -> vector[der] < m -> vector[min]) {
        min = der;
    }
    if (min != i) {
        intercambiar(&m -> vector[i], &m -> vector[min]);
        hundir(m, min);
    }
}

void crearMonticulo(pmonticulo m, int v[], int n) {
    iniMonticulo(m);
    int i;
    for (i = 0; i < n; i++) {
        m -> vector[i] = v[i];
    }
    m -> ultimo = n - 1;
    for (i = (n - 1) / 2; i >= 0; i--) {
        hundir(m, i);
    }
}

void flotar(pmonticulo m, int i) {
    while (i > 0 && m -> vector[(i - 1) / 2] < m -> vector[i-1]) {
        intercambiar(&m -> vector[(i - 1) / 2], &m -> vector[i-1]);
        i = (i - 1) / 2;
    }
}

void insertarMonticulo(pmonticulo m, int x) {
    if (m == NULL) {
        printf("Error: Montículo no inicializado\n");
        return;
    }
    if (m->ultimo + 1 == TAM) {
        printf("Error: Montículo lleno\n");
        return;
    }
    m -> ultimo++;
    m -> vector[m -> ultimo] = x;
    flotar(m, m -> ultimo);
}

void quitarMenor(pmonticulo m) {
    if (m -> ultimo < 0) {
        printf("Error: Montículo vacío\n");
        return;
    }
    m -> vector[0] = m -> vector[m->ultimo];
    m -> ultimo--;
    hundir(m, 0);
}

int consultarMenor(const pmonticulo m) {
    if (m -> ultimo < 0) {
        printf("El montículo está vacío.\n");
        return -1;
    }
    return m -> vector[0];
}

void ordenarPorMonticulos(int v[], int n) {
    pmonticulo m = (pmonticulo) malloc(sizeof(struct monticulo));
    crearMonticulo(m, v, n);
    int i;
    for (i = 0; i < n; i++) {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }
    free(m);
}

void testOrdenarPorMonticulos() {
    int v[N], i;
    void (*tipos[3])(int[], int) = {aleatorio, ascendente, descendente};
    char *tipo[3] = {"aleatorio", "ascendente", "descendente"};

    for (i = 0; i < 3; i++) {
        tipos[i](v, N);

        printf("Montículo %s inicial: ", tipo[i]);
        listar_vector(v, N);

        ordenarPorMonticulos(v, N);

        printf("Montículo %s ordenado: ", tipo[i]);
        listar_vector(v, N);

        estaOrdenado(v, N);
    }
}

void ejecutarAlgoritmo(int tipo, int *v, pmonticulo m, int tam) {
    int i;
    if (tipo == ORDENAR) {
        ordenarPorMonticulos(v, tam);
    } else if (tipo == CREAR) {
        crearMonticulo(m, v, tam);
    } else if (tipo == INSERTAR) {
        iniMonticulo(m);
        for(i = 0; i < tam; i++) {
            insertarMonticulo(m, v[i]);
        }
    }
}
int inicializarEstructuras(int tipo, int tam, void (*f_ini)(int [], int), 
                          int v[], pmonticulo *m) {
    if (tipo == ORDENAR) {
        if (f_ini == NULL) {
            return -1;
        }
        f_ini(v, tam);
    }
    
    if (tipo == CREAR || tipo == INSERTAR) {
        *m = (pmonticulo)malloc(sizeof(struct monticulo));
        if (*m == NULL) {
            return -1;
        }
    }
    return 0;
}

double medirTiempo(int tipo, int tam, int k, void (*f_ini)(int [], int)) {
    double t_test = 0.0, t_test_init = 0.0;
    double t_inicio = 0.0, t_fin = 0.0;
    int *v = malloc(tam * sizeof(int));
    int i;
    pmonticulo m = NULL;

    if (inicializarEstructuras(tipo, tam, f_ini, v, &m) == -1) {
        free(v);
        return -1;
    }        

    t_inicio = microsegundos();
    ejecutarAlgoritmo(tipo, v, m, tam);
    t_fin = microsegundos();
    t_test = t_fin - t_inicio;

    if (t_test < 500) {
        printf("(*)");
        t_test_init = 0.0;
        for (i = 0; i < k; i++) {
            if (tipo == ORDENAR) {
                f_ini(v, tam);
            }
            t_inicio = microsegundos();
            ejecutarAlgoritmo(tipo, v, m, tam);
            t_fin = microsegundos();
            t_test_init += t_fin - t_inicio;
        }
        t_test = t_test_init / k;
    }

    free(v);
    if (m != NULL){
        free(m);
    }
    return t_test;
}

void tiemposCrearMonticulo(){
    int k = 1000, n, i;
    double tiempo = 0.0;
    for (i = 0; i < REPETITIONS; i++) {
        printf("\nMedición de tiempo para crearMonticulo de forma ascendente:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(CREAR, n, k, ascendente);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, tiempo/pow(n, 0.8), tiempo/n, tiempo/pow(n, 1.2));
        }
        printf("\nu(n) = nlog(n)^0.8\na(n) = n\no(n) = n^1.2\n");

        printf("\nMedición de tiempo para crearMonticulo de forma descendente:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(CREAR, n, k, descendente);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, tiempo/pow(n, 0.8), tiempo/n, tiempo/pow(n, 1.2));
        }
        printf("\nu(n) = nlog(n)^0.8\na(n) = n\no(n) = n^1.2\n");

        printf("\nMedición de tiempo para crearMonticulo de forma aleatoria:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(CREAR, n, k, aleatorio);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, tiempo/pow(n, 0.8), tiempo/n, tiempo/pow(n, 1.2));
        }
        printf("\nu(n) = nlog(n)^0.8\na(n) = n\no(n) = n^1.2\n");
    }
}
void tiemposInsertarMonticulo(){
    int k = 1000, n, i;
    double tiempo = 0.0;
    for (i = 0; i < REPETITIONS; i++) {
        printf("\nMedición de tiempo para insertarMonticulo de forma ascendente:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(INSERTAR, n, k, ascendente);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, 
                tiempo/pow(n*log(n), 0.8), // cota sobreestimada
                tiempo/(n*log(n)),          // cota sobreestimada
                tiempo/pow(n*log(n), 1.1)); // cota sobreestimada
        }
        printf("\nu(n) = n*log(n)\na(n) = n*log(n)\no(n) = n*log(n)^2\n");

        printf("\nMedición de tiempo para insertarMonticulo de forma descendente:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(INSERTAR, n, k, descendente);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, 
                tiempo/pow(n*log(n), 0.8), // cota sobreestimada
                tiempo/(n*log(n)), // cota sobreestimada
                tiempo/pow(n*log(n), 1.1)); // cota sobreestimada
        }
        printf("\nu(n) = n*log(n)\na(n) = n*log(n)\no(n) = n*log(n)^2\n");

        printf("\nMedición de tiempo para insertarMonticulo de forma aleatoria:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(INSERTAR, n, k, aleatorio);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, 
                tiempo/pow(n*log(n), 0.8), // cota sobreestimada
                tiempo/(n*log(n)), // cota sobreestimada
                tiempo/pow(n*log(n), 1.1)); // cota sobreestimada
        }
        printf("\nu(n) = n*log(n)\na(n) = n*log(n)\no(n) = n*log(n)^2\n");
    }
}

void tiemposOrdenarMonticulo(){
    int k = 1000, n, i;
    double tiempo = 0.0;

    for (i = 0; i < REPETITIONS; i++) {
        printf("\nMedición de tiempo para ordenarMonticulo de forma ascendente:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(ORDENAR, n, k, ascendente);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, tiempo/pow((n*log(n)), 0.85), tiempo/(n*log(n)), 
                                                tiempo/pow((n*log(n)), 1.2));
        }
        printf("\nu(n) = nlog(n)^0.85\na(n) = nlog(n)\no(n) = nlog(n)^1.2\n");

        printf("\nMedición de tiempo para ordenarMonticulo de forma descendente:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(ORDENAR, n, k, descendente);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, tiempo/pow((n*log(n)), 0.85), 
                           tiempo/pow((n*log(n)), 0.98), 
                           tiempo/pow((n*log(n)), 1.2));
        }
        printf("\nu(n) = nlog(n)^0.85\na(n) = nlog(n)^0.98\no(n) = nlog(n)^1.2\n");

        printf("\nMedición de tiempo para ordenarMonticulo de forma aleatoria:\n");
        printf("\t     n \t \t\t\tt(n) \t\tt(n)/u(n)");
        printf("\t\tt(n)/a(n) \t\tt(n)/o(n)\n");
        for (n = 1000; n <= MAX_NUM; n *= 2) {
            tiempo = medirTiempo(ORDENAR, n, k, aleatorio);
            printf("\t%8d\t\t%15.4f\t\t%14.12f\t\t%14.12f\t\t%14.12f\n",
                n, tiempo, tiempo/pow((n*log(n)), 0.85), tiempo/(n*log(n)), 
                                                tiempo/pow((n*log(n)), 1.2));
        }
        printf("\nu(n) = nlog(n)^0.85\na(n) = nlog(n)\no(n) = nlog(n)^1.2\n");
    }
}

int main() {
    inicializar_semilla();
    //testOrdenarPorMonticulos();
    //tiemposCrearMonticulo();
    tiemposInsertarMonticulo();
    //tiemposOrdenarMonticulo();
    return 0;
}