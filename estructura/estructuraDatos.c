#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
    Estructura Nodo:
    - Representa cada elemento de la cola.
    - Contiene el valor del nodo y un puntero al siguiente nodo.
*/
struct Nodo {
    int valor;
    struct Nodo* siguiente;
};

/*
    Estructura ColaMinimo:
    - front: puntero al primer nodo (cabeza de la cola).
    - rear: puntero al último nodo (final de la cola).
*/
struct ColaMinimo {
    struct Nodo* front;
    struct Nodo* rear;
};

/*
    Crear un nuevo nodo con un valor dado.
*/
struct Nodo* crearNodo(int valor) {
    struct Nodo* nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
    nuevo->valor = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

/*
    Inicializa una ColaMinimo vacía.
*/
void inicializarCola(struct ColaMinimo* cola) {
    cola->front = NULL;
    cola->rear = NULL;
}

/*
    Método encolar:
    - Inserta un valor al final de la cola (FIFO).
*/
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

/*
    Método desencolar:
    - Elimina el valor del frente de la cola.
    - Devuelve el valor eliminado, o INT_MIN si la cola está vacía.
*/
int desencolar(struct ColaMinimo* cola) {
    if (cola->front == NULL) {
        printf("La cola está vacía. No se puede desencolar.\n");
        return INT_MIN;
    }

    struct Nodo* temp = cola->front;
    int valor = temp->valor;

    cola->front = cola->front->siguiente;

    if (cola->front == NULL) {
        cola->rear = NULL; // La cola quedó vacía
    }

    free(temp);
    return valor;
}

/*
    Método minimo:
    - Recorre la cola y devuelve el valor mínimo.
    - Si está vacía, devuelve INT_MAX.
*/
int minimo(struct ColaMinimo* cola) {
    if (cola->front == NULL) {
        printf("La cola está vacía. No hay mínimo.\n");
        return INT_MAX;
    }

    int min = cola->front->valor;
    struct Nodo* actual = cola->front;

    while (actual != NULL) {
        if (actual->valor < min) {
            min = actual->valor;
        }
        actual = actual->siguiente;
    }

    return min;
}

/*
    Función principal para probar la ColaMinimo
*/
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

    desencolar(&cola); // 3
    desencolar(&cola); // 7

    printf("Mínimo actual: %d\n", minimo(&cola)); // 2

    desencolar(&cola); // 2
    minimo(&cola); // La cola está vacía

    return 0;
}
