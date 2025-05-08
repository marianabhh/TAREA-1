#include <stdio.h>

int encontrar_maximo(int arr[], int n) {
int maximo = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < maximo) {
            maximo = arr[i];
        }
    }
    return maximo;
}

int main() {
        int numeros[] = {10, 1, 5, 40, 0};
        int n = sizeof(numeros) / sizeof(numeros[0]);
        int maximo = encontrar_maximo(numeros, n);
        printf("El número mas grande es: %d\n", maximo);
    return 0;
}