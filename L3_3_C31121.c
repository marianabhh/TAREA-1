#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANO 5

void llenarMatrizAleatoria(int matriz[TAMANO][TAMANO]) {
    srand(time(NULL));
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            matriz[i][j] = rand() % 2;
        }
    }
}

void imprimirMatriz(int matriz[TAMANO][TAMANO]) {
    printf("Matriz generada:\n");
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Recorre toda la matriz en orden ↙ y busca la secuencia más larga de 1s consecutivos
int encontrar_max_secuencia_diagonal_global(int matriz[TAMANO][TAMANO]) {
    int max = 0, contador = 0;

    // Recorre diagonales comenzando en (0,0)
    for (int suma = 0; suma <= 2 * (TAMANO - 1); suma++) {
        for (int i = 0; i <= suma; i++) {
            int j = suma - i;
            if (i < TAMANO && j < TAMANO) {
                if (matriz[i][j] == 1) {
                    contador++;
                    if (contador > max) max = contador;
                } else {
                    contador = 0;
                }
            }
        }
    }

    return max;
}

int main() {
    int matriz[TAMANO][TAMANO] = {
    
    };

    llenarMatrizAleatoria(matriz);

    imprimirMatriz(matriz);

    int max_secuencia = encontrar_max_secuencia_diagonal_global(matriz);
    printf("\nLa secuencia más larga de 1s consecutivos en recorrido ↓↙ es: %d\n", max_secuencia);

    return 0;
}