#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TAM 100

// Función para verificar si un número es binario (0 o 1)
int es_binario(int num) {
    return num == 0 || num == 1;
}

// Leer matriz desde archivo
int leerMatrizDesdeArchivo(const char* nombre_archivo, int matriz[MAX_TAM][MAX_TAM], int* tamano) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return 0;
    }

    int filas = 0, columnas = -1;
    char linea[1024];

    while (fgets(linea, sizeof(linea), archivo)) {
        int col = 0;
        char* token = strtok(linea, " \n");
        while (token != NULL) {
            int num = atoi(token);
            if (!es_binario(num)) {
                printf("Error: La matriz contiene un valor no binario: %d\n", num);
                fclose(archivo);
                return 0;
            }
            matriz[filas][col++] = num;
            token = strtok(NULL, " \n");
        }

        if (columnas == -1) columnas = col;
        else if (col != columnas) {
            printf("Error: La matriz no es cuadrada (filas con diferente longitud).\n");
            fclose(archivo);
            return 0;
        }

        filas++;
    }

    fclose(archivo);

    if (filas != columnas) {
        printf("Error: La matriz no es cuadrada (%d filas, %d columnas).\n", filas, columnas);
        return 0;
    }

    *tamano = filas;
    return 1;
}

// Imprimir matriz
void imprimirMatriz(int matriz[MAX_TAM][MAX_TAM], int tamano) {
    printf("Matriz leída desde el archivo:\n");
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Recorrido en dirección ↖ (↓↙) incluyendo continuidad entre diagonales
int encontrar_max_secuencia_diagonal_global(int matriz[MAX_TAM][MAX_TAM], int tamano) {
    int max = 0, contador = 0;

    for (int suma = 0; suma <= 2 * (tamano - 1); suma++) {
        for (int i = tamano - 1; i >= 0; i--) {
            int j = suma - i;
            if (j >= 0 && j < tamano) {
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
    int matriz[MAX_TAM][MAX_TAM];
    int tamano;

    if (!leerMatrizDesdeArchivo("matriz.txt", matriz, &tamano)) {
        return 1;
    }

    imprimirMatriz(matriz, tamano);

    int max_secuencia = encontrar_max_secuencia_diagonal_global(matriz, tamano);
    printf("\nLa secuencia más larga de 1s consecutivos en dirección (↓↙) es: %d\n", max_secuencia);

    return 0;
}