#include <stdio.h>

int main (void){
    float HARGA;
    float BERAT;
    float hasil;

    scanf ("%f", &HARGA);
    scanf ("%f", &BERAT);
    hasil = HARGA * BERAT / 1000;

    printf  ("%.2f", hasil);

    return 0;
}