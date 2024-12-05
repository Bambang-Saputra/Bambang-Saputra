#include <stdio.h>
int main (void){
    float HARGA ;
    float BERAT ;
    scanf ("%f", &HARGA);
    scanf ("%f", &BERAT);
    float total = HARGA * BERAT / 1000 ;
    printf ("%.2f\n", total);

    return 0;
}