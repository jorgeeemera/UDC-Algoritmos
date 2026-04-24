/*
Alumno 1: Adrián Novio Vilariño
Alumno 2: Pablo Araújo Rodríguez
Alumno 3: Jorge Mera Hermida 
*/

#include "dispersion.h"

void inicializar_semilla () {
	srand(time(NULL));
}

double microsegundos (){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

// Función para inicializar la tabla de dispersión
void inicializar_cerrada(tabla_cerrada *diccionario, int tam){
    *diccionario = malloc(tam * sizeof(entrada));
    int i;
    for (i = 0; i < tam; i++)
    {
        (*diccionario)[i].ocupada = 0;
        (*diccionario)[i].clave[0] = '\0';
        (*diccionario)[i].sinonimos[0] = '\0';
    }
}

unsigned int exploracion_lineal(int pos_ini, int num_intento){
    return (pos_ini + num_intento);
}

unsigned int exploracion_cuadratica(int pos_ini, int num_intento){
    return (pos_ini + num_intento * num_intento);
}

unsigned int exploracion_doble(int pos_ini, int num_intento){
    return (pos_ini + (10007 - (pos_ini % 10007)) * num_intento);
}

unsigned int ndispersion(char *clave, int tamTabla){
    if (strcmp(clave, "ANA") == 0)
        return 7;
    if (strcmp(clave, "JOSE") == 0)
        return 7;
    if (strcmp(clave, "OLGA") == 0)
        return 7;
    return 6;
}

// Función para insertar en la tabla cerrada
int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario,
    int tam, unsigned int (*dispersion)(char *, int),
    unsigned int (*resol_colisiones)(int, int)) {
    int colisiones = 0;
    int pos_ini = dispersion(clave, tam);
    int pos = pos_ini;

    while ((*diccionario)[pos].ocupada) {
        colisiones++;
        pos = (*resol_colisiones)(pos_ini, colisiones) % tam;
    }

    if (!((*diccionario)[pos].ocupada)){
        strcpy((*diccionario)[pos].clave, clave);
        strcpy((*diccionario)[pos].sinonimos, sinonimos);
        (*diccionario)[pos].ocupada = 1;
    }
    return colisiones; // Retornar colisiones de esta inserción
}

// Función para buscar en la tabla cerrada
pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
    int *colisiones, unsigned int (*dispersion)(char *, int),
    unsigned int (*resol_colisiones)(int, int)){
    *colisiones = 0;
    int intento = 0;
    int pos_ini = dispersion(clave, tam);
    int pos = pos_ini;

    while (diccionario[pos].ocupada){
        if (strcmp(diccionario[pos].clave, clave) == 0){
            return pos; // Encontrado
        }
        (*colisiones)++;
        intento++;
        pos = resol_colisiones(pos_ini, intento) % tam; // Actualizar la posición
    }
    return -1; // No encontrado
}

// Función para mostrar el contenido de la tabla
void mostrar_cerrada(tabla_cerrada diccionario, int tam){
    printf("{\n");
    int i;
    for (i = 0; i < tam; i++){
        if (diccionario[i].ocupada){
            printf("%d- (%s : %s)\n", i, diccionario[i].clave,
                                            diccionario[i].sinonimos);
        }
        else {
            printf("%d-\n", i);
        }
    }
    printf("}\n");
}

void test_lineal(tabla_cerrada diccionario_lineal) {
    char *claves[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN"};
    char *sinonimos[] = {
        "Ejemplo sinónimo de ANA", "Ejemplo sinónimo de LUIS",
        "Ejemplo sinónimo de JOSE", "Ejemplo sinónimo de OLGA",
        "Ejemplo sinónimo de ROSA", "Ejemplo sinónimo de IVAN"};
    
    int i;
    int total_colisiones_lineal = 0;
    for (i = 0; i < 6; i++){
        total_colisiones_lineal += insertar_cerrada(claves[i], sinonimos[i],
                &diccionario_lineal, TAM_TABLA, ndispersion,
                exploracion_lineal);
    }

    printf("\n\n**TABLA CERRADA LINEAL**\n");
    mostrar_cerrada(diccionario_lineal, TAM_TABLA);
    printf("Numero total de colisiones al insertar los elementos: %d\n",
                                                    total_colisiones_lineal);

    int colisiones = 0;
    char *buscar_claves[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA",
                                                    "IVAN", "CARLOS"};
    for (i = 0; i < 7; i++){
        int pos = buscar_cerrada(buscar_claves[i], diccionario_lineal,
                        TAM_TABLA, &colisiones, ndispersion,
                        exploracion_lineal);
        if (pos != -1) {
            printf("Al buscar: %s, encuentro: %s, colisiones: %d\n",
            buscar_claves[i],  diccionario_lineal[pos].clave, colisiones);
        }
        else {
            printf("No encuentro: %s, colisiones: %d\n",
                        buscar_claves[i], colisiones);
        }
    }
}

void test_cuadratica(tabla_cerrada diccionario_cuadratico){
    // Definimos las claves y los sinónimos en arrays
    char *claves[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN"};
    char *sinonimos[] = {
        "Ejemplo sinónimo de ANA", "Ejemplo sinónimo de LUIS",
        "Ejemplo sinónimo de JOSE", "Ejemplo sinónimo de OLGA",
        "Ejemplo sinónimo de ROSA", "Ejemplo sinónimo de IVAN"};
    // Inserción de elementos en la tabla cerrada cuadrática
    int total_colisiones_cuadratica = 0;
    int i;
    for (i = 0; i < 6; i++){
        total_colisiones_cuadratica += insertar_cerrada(claves[i],
            sinonimos[i], &diccionario_cuadratico,
            TAM_TABLA, ndispersion, exploracion_cuadratica);
    }
    printf("\n\n**TABLA CERRADA CUADRATICA**\n");
    mostrar_cerrada(diccionario_cuadratico, TAM_TABLA);
    printf("Numero total de colisiones al insertar los elementos: %d\n",
           total_colisiones_cuadratica);
    // Búsqueda en la tabla cerrada cuadrática
    int colisiones = 0;
    char *buscar_claves[] = {"ANA", "LUIS", "JOSE", "OLGA",
        "ROSA", "IVAN", "CARLOS"};
    for (i = 0; i < 7; i++){
        int pos = buscar_cerrada(buscar_claves[i], diccionario_cuadratico,
            TAM_TABLA, &colisiones, ndispersion, exploracion_cuadratica);
        if (pos != -1)
        {
            printf("Al buscar: %s, encuentro: %s, colisiones: %d\n",
                buscar_claves[i], diccionario_cuadratico[pos].clave, colisiones);
        }
        else
        {
            printf("No encuentro: %s, colisiones: %d\n",
                buscar_claves[i], colisiones);
        }
    }
}

int insertar_sinonimos(tabla_cerrada *diccionario, item *datos, int num_items,
    int tam_tabla, unsigned int (*dispersion)(char *, int),
    unsigned int (*resol_colisiones)(int, int)){
    int total_colisiones = 0;
    int i; 
    for (i = 0; i < num_items; i++)
    {
        total_colisiones += insertar_cerrada(datos[i].clave,
            datos[i].sinonimos, diccionario, tam_tabla,
            dispersion, resol_colisiones);
    }
    return total_colisiones;
}

// Función para imprimir el contenido de una tabla y el número total de colisiones
void imprimir_tabla_y_colisiones(char *nombre_tabla,
    tabla_cerrada diccionario, int tam_tabla, int total_colisiones){
    printf("\n\n**%s**\n", nombre_tabla); 
    printf("Numero total de colisiones: %d\n", total_colisiones);
}

void probar_tablas(item *datos, int num_items, int tam_tabla){
    tabla_cerrada diccionario_lineal_B, diccionario_cuadratico_B,
    diccionario_doble_B;
    tabla_cerrada diccionario_lineal_A, diccionario_cuadratico_A,
    diccionario_doble_A;
    // Inicializar las tablas cerradas
    inicializar_cerrada(&diccionario_lineal_B, tam_tabla);
    inicializar_cerrada(&diccionario_cuadratico_B, tam_tabla);
    inicializar_cerrada(&diccionario_doble_B, tam_tabla);
    inicializar_cerrada(&diccionario_lineal_A, tam_tabla);
    inicializar_cerrada(&diccionario_cuadratico_A, tam_tabla);
    inicializar_cerrada(&diccionario_doble_A, tam_tabla);
    // Insertar los sinónimos y contar las colisiones para cada tipo de dispersión
    int total_colisiones_lineal_B = insertar_sinonimos(&diccionario_lineal_B,
        datos, num_items, tam_tabla, dispersionB, exploracion_lineal);
    int total_colisiones_cuadratico_B = insertar_sinonimos(&diccionario_cuadratico_B,
        datos, num_items, tam_tabla, dispersionB, exploracion_cuadratica);
    int total_colisiones_doble_B = insertar_sinonimos(&diccionario_doble_B,
        datos, num_items, tam_tabla, dispersionB, exploracion_doble);

    int total_colisiones_lineal_A = insertar_sinonimos(&diccionario_lineal_A,
        datos, num_items, tam_tabla, dispersionA, exploracion_lineal);
    int total_colisiones_cuadratico_A = insertar_sinonimos(&diccionario_cuadratico_A,
        datos, num_items, tam_tabla, dispersionA, exploracion_cuadratica);
    int total_colisiones_doble_A = insertar_sinonimos(&diccionario_doble_A,
        datos, num_items, tam_tabla, dispersionA, exploracion_doble);
    // Imprimir los resultados
    imprimir_tabla_y_colisiones("TABLA CERRADA LINEAL CON DISPERSION B",
        diccionario_lineal_B, tam_tabla, total_colisiones_lineal_B);
    imprimir_tabla_y_colisiones("TABLA CERRADA CUADRATICA CON DISPERSION B",
        diccionario_cuadratico_B, tam_tabla, total_colisiones_cuadratico_B);
    imprimir_tabla_y_colisiones("TABLA CERRADA DOBLE CON DISPERSION B",
        diccionario_doble_B, tam_tabla, total_colisiones_doble_B);

    imprimir_tabla_y_colisiones("TABLA CERRADA LINEAL CON DISPERSION A",
        diccionario_lineal_A, tam_tabla, total_colisiones_lineal_A);
    imprimir_tabla_y_colisiones("TABLA CERRADA CUADRATICA CON DISPERSION A",
        diccionario_cuadratico_A, tam_tabla, total_colisiones_cuadratico_A);
    imprimir_tabla_y_colisiones("TABLA CERRADA DOBLE CON DISPERSION A",
        diccionario_doble_A, tam_tabla, total_colisiones_doble_A);
}

void imprimir_tiempos(int n, double t, int umbral,
    unsigned int (resolucion_colisiones)(int, int),
    unsigned int (*dispersion)(char*, int)) {
    double sub, ajust, sobre;
    // Selección de fórmula según el tipo de resolución y dispersión
    if (resolucion_colisiones == exploracion_lineal
        && dispersion == dispersionA) {
        sub = t/pow(n, 0.8); ajust = t/n; sobre = t/(n*log(n));
    }
    else if (resolucion_colisiones == exploracion_cuadratica
        && dispersion == dispersionA) {
        sub = t / pow(n, 0.95); ajust = t/n; sobre = t / pow(n, 1.1);
    }
    else if (resolucion_colisiones == exploracion_doble
        && dispersion == dispersionA) {
        sub = t/pow(n, 0.8); ajust = t/pow(n, 0.95); sobre = t/pow(n, 1.1);
    }
    else if (resolucion_colisiones == exploracion_lineal
        && dispersion == dispersionB) {
        sub = t/pow(n, 0.9); ajust = t/pow(n, 1.1); sobre = t/(n * log(n));
    }
    else if (resolucion_colisiones == exploracion_cuadratica
        && dispersion == dispersionB) {
        sub = t/pow(n, 0.8); ajust = t/n; sobre = t/(n * log(n));
    }
    else if (resolucion_colisiones == exploracion_doble
        && dispersion == dispersionB) {
        sub = t/pow(n, 0.8); ajust = t/n; sobre = t/pow(n, 1.2);
    }
    // Imprimir resultados alineados
    if (umbral == 1) {
        printf("(*)%10d %15.3f %18.7f %13.7f %16.7f\n",
            n, t, sub, ajust, sobre);
    } else {
        printf("   %10d %15.3f %18.7f %13.7f %16.7f\n",
            n, t, sub, ajust, sobre);
    }
}

void imprimir_cotas(unsigned int (*exploracion_func)(int, int),
    unsigned int (*dispers_func)(char *, int)) {
    if (exploracion_func == exploracion_lineal
        && dispers_func == dispersionA) {
        printf("%12s %14s %20s %10s %25s\n",
            "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/(n*(log(n)))");
    }
    else if (exploracion_func == exploracion_cuadratica
        && dispers_func == dispersionA) {
        printf("%12s %14s %20s %11s %19s\n",
            "n", "t(n)", "t(n)/n^0.95", "t(n)/n", "t(n)/n^1.1");
    }
    else if (exploracion_func == exploracion_doble
        && dispers_func == dispersionA) {
        printf("%12s %14s %20s %14s %15s\n",
            "n", "t(n)", "t(n)/n^0.8", "t(n)/n^0.95", "t(n)/n^1.1");
    }
    else if (exploracion_func == exploracion_lineal
        && dispers_func == dispersionB) {
        printf("%12s %14s %20s %14s %22s\n",
            "n", "t(n)", "t(n)/n^0.9", "t(n)/n^1.1", "t(n)/(n*(log(n)))");
    }
    else if (exploracion_func == exploracion_cuadratica
        && dispers_func == dispersionB) {
        printf("%12s %14s %20s %11s %25s\n",
            "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/(n*(log(n)))");
    }
    else if (exploracion_func == exploracion_doble
        && dispers_func == dispersionB) {
        printf("%12s %14s %20s %12s %18s\n",
            "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
    }
}

void imprimir_cabeceras(unsigned int (*exploracion_func)(int, int),
    unsigned int (*dispers_func)(char *, int), int num_items, int colisiones) {
    if (exploracion_func == exploracion_lineal
        && dispers_func == dispersionA) {
        printf("* Dispersión cerrada lineal con dispersionA *\n");
    } else if (exploracion_func == exploracion_cuadratica
        && dispers_func == dispersionA) {
        printf("* Dispersión cerrada cuadrática con dispersionA *\n");
    } else if (exploracion_func == exploracion_doble
        && dispers_func == dispersionA) {
        printf("* Dispersión cerrada doble con dispersionA *\n");
    } else if (exploracion_func == exploracion_lineal
        && dispers_func == dispersionB) {
        printf("* Dispersión cerrada lineal con dispersionB *\n");
    } else if (exploracion_func == exploracion_cuadratica
        && dispers_func == dispersionB) {
        printf("* Dispersión cerrada cuadrática con dispersionB *\n");
    } else if (exploracion_func == exploracion_doble
        && dispers_func == dispersionB) {
        printf("* Dispersión cerrada doble con dispersionB *\n");
    }
    printf("Insertando %d elementos... Número total de colisiones: %d\n",
        num_items, colisiones);
    printf("Buscando n elementos...\n\n");
    imprimir_cotas(exploracion_func, dispers_func);
}

double medir_tiempos(item *datos, int num_items, int k,
    unsigned int (*exploracion_func)(int, int),
    unsigned int (*dispers_func)(char *, int)) {
    double t_test = 0.0, t_inicio = 0.0, t_fin = 0.0;
    int i, j, n, ran, umbral;
    int colisiones_insertar, colisiones_buscar = 0;
    tabla_cerrada diccionario;
    // Inicializar y rellenar la tabla
    inicializar_cerrada(&diccionario, TAM_TABLA_FINAL);
    colisiones_insertar = insertar_sinonimos(&diccionario, datos, num_items,
                            TAM_TABLA_FINAL, dispers_func, exploracion_func);
    imprimir_cabeceras(exploracion_func, dispers_func,
        num_items, colisiones_insertar);
    for (n = 125; n <= MAX_NUM; n *= 2){
        t_inicio = microsegundos(); umbral = 0;
        for (j = 0; j < n; j++){
            ran = rand() % (num_items - 1);
            buscar_cerrada(datos[ran].clave, diccionario, num_items,
                &colisiones_buscar, dispers_func, exploracion_func);
        }
        t_fin = microsegundos();
        t_test = t_fin - t_inicio;
        if (t_test < 500) {
            umbral = 1;
            t_inicio = microsegundos();
            for (i = 0; i < k; i++){
                for (j = 0; j < n;j++){
					ran = rand() % (num_items - 1);
                    buscar_cerrada(datos[ran].clave, diccionario, num_items,
                        &colisiones_buscar, dispers_func, exploracion_func);
                }
            }
            t_fin = microsegundos();
            t_test = (t_fin - t_inicio) / k;
        }
        imprimir_tiempos(n, t_test, umbral, exploracion_func, dispers_func);
    }
    printf("\n\n");
    free(diccionario);
    return t_test;
}

int main() {

    tabla_cerrada d = malloc (38197 * sizeof(entrada));
    int max_items = 19062;

    item datos[max_items];

    // Se leen los sinónimos del archivo
    int num_items = leer_sinonimos(datos);
    if (num_items == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    //inicializar_cerrada(&d, TAM_TABLA);
    //test_cuadratica(d);
    //inicializar_cerrada(&d, TAM_TABLA);
    //test_lineal(d);

    medir_tiempos(datos, num_items, 1000, exploracion_lineal, dispersionA);
    medir_tiempos(datos, num_items, 1000, exploracion_cuadratica, dispersionA);
    medir_tiempos(datos, num_items, 1000, exploracion_doble, dispersionA);

    medir_tiempos(datos, num_items, 1000, exploracion_lineal, dispersionB);
    medir_tiempos(datos, num_items, 1000, exploracion_cuadratica, dispersionB);
    medir_tiempos(datos, num_items, 1000, exploracion_doble, dispersionB);

    free(d);

    return 0;
}