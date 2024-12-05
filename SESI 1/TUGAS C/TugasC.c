#include <stdio.h>

int main (void) {
    int X ,Y ;
    char tambah ;
    scanf("%d %c %d", &X, &tambah ,&Y);
    int N = X + Y;
    printf("%d\n", N);

    return 0;
}