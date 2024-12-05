#include <stdio.h>

int main (void){
    int angka1, angka2, angka3;
    int angka_tengah1, angka_tengah2, angka_tengah3;

    scanf ("%d", &angka1);
    scanf ("%d", &angka2);
    scanf ("%d", &angka3);

    angka_tengah1 = (angka1 / 10) % 10;
    angka_tengah2 = (angka2 / 10) % 10;
    angka_tengah3 = (angka3 / 10) % 10;

    printf ("%d\n", angka_tengah1);
    printf ("%d\n", angka_tengah2);
    printf ("%d\n", angka_tengah3);

    return 0;
}