#include <stdio.h>

int main() {
    int matriz[7][7] = {
        {1, 2, 0, 3, 4, 1, 5},
        {3, 0, 4, 2, 1, 5, 0},
        {2, 4, 1, 0, 3, 2, 4},
        {5, 1, 3, 4, 0, 2, 1},
        {0, 3, 2, 1, 5, 4, 2},
        {4, 5, 1, 2, 3, 0, 3},
        {1, 2, 4, 5, 2, 3, 0}
    };

    int n = 7; // Tamaño de la matriz

    // Imprimir la matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Suma de la diagonal principal
    int suma_principal = 0;
    for (int i = 0; i < n; i++) {
        suma_principal += matriz[i][i];
    }
    printf("\nSuma diagonal principal: %d\n", suma_principal);

    // Suma de la diagonal secundaria
    int suma_secundaria = 0;
    for (int i = 0; i < n; i++) {
        suma_secundaria += matriz[i][n - i - 1];
    }
    printf("Suma diagonal secundaria: %d\n", suma_secundaria);

    // Suma de todas las diagonales IZQUIERDA-DERECHA (de arriba hacia abajo)
    printf("\nSuma diagonales izquierda-derecha:\n");
    for (int d = 0; d < 2 * n - 1; d++) {
        int suma = 0;
        for (int i = 0; i < n; i++) {
            int j = d - i;
            if (j >= 0 && j < n) {
                suma += matriz[i][j];
            }
        }
        printf("Diagonal %d: Suma = %d\n", d, suma);
    }

    // Suma de todas las diagonales DERECHA-IZQUIERDA (de arriba hacia abajo)
    printf("\nSuma diagonales derecha-izquierda:\n");
    for (int d = 0; d < 2 * n - 1; d++) {
        int suma = 0;
        for (int i = 0; i < n; i++) {
            int j = (n - 1) - (d - i);
            if (j >= 0 && j < n) {
                suma += matriz[i][j];
            }
        }
        printf("Diagonal %d: Suma = %d\n", d, suma);
    }

    return 0;
}