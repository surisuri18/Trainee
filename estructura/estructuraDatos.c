#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Nodo {
    int valor;
    struct Nodo* siguiente;
};

struct ColaMinimo {
    struct Nodo* front;
    struct Nodo* rear; // solo para encolar
};

struct Nodo* crearNodo(int valor) {
    struct Nodo* nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
    nuevo->valor = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

void inicializarCola(struct ColaMinimo* cola) {
    cola->front = NULL;
    cola->rear = NULL;
}

void encolar(struct ColaMinimo* cola, int valor) {
    struct Nodo* nuevo = crearNodo(valor);

    if (cola->rear == NULL) {
        cola->front = nuevo;
        cola->rear = nuevo;
    } else {
        cola->rear->siguiente = nuevo;
        cola->rear = nuevo;
    }
}

int desencolar(struct ColaMinimo* cola) {
    if (cola->front == NULL) {
        printf("La cola está vacía. No se puede desencolar.\n");
        return INT_MIN;
    }

    struct Nodo* temp = cola->front;
    int valor = temp->valor;

    cola->front = cola->front->siguiente;
    if (cola->front == NULL) cola->rear = NULL; // la cola quedó vacía

    free(temp);
    return valor;
}

int minimo(struct ColaMinimo* cola) {
    if (cola->front == NULL) {
        printf("La cola está vacía. No hay mínimo.\n");
        return INT_MAX;
    }

    int min = cola->front->valor;
    struct Nodo* actual = cola->front;

    // recorremos hasta que actual sea NULL, no necesitamos puntero extra
    while (actual != NULL) {
        if (actual->valor < min) min = actual->valor;
        actual = actual->siguiente;
    }

    return min;
}

int main() {
    struct ColaMinimo cola;
    inicializarCola(&cola);

    encolar(&cola, 5);
    encolar(&cola, 3);
    encolar(&cola, 7);
    encolar(&cola, 2);

    printf("Mínimo actual: %d\n", minimo(&cola)); // 2
    printf("Desencolado: %d\n", desencolar(&cola)); // 5
    printf("Mínimo actual: %d\n", minimo(&cola)); // 2

    printf("Desencolado: %d\n", desencolar(&cola)); // 3
    printf("Desencolado: %d\n", desencolar(&cola)); // 7
    printf("Mínimo actual: %d\n", minimo(&cola)); // 2

    printf("Desencolado: %d\n", desencolar(&cola)); // 2
    minimo(&cola); // cola vacía

    return 0;
}
