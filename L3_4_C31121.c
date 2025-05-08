#include <stdio.h>

int main() {
    int num, bin = 0, rem = 0, place = 1;

    printf("Ingrese un número entero\n");
    scanf("%d", &num);

    printf("\nEl equivalente binario de %d es ", num);
    while(num)
    {
        rem = num % 2;
        num = num / 2;
        bin = bin + (rem * place);
        place = place * 10;
    }
    printf("%d\n", bin);
}