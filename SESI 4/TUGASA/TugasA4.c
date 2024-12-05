#include <stdio.h>

int main (void){
    float F;
    int angkaPertama, angkaKedua;

    scanf ("%f", &F);

    angkaPertama = ((int)(F * 100)) % 10; //pembulatan angka pertama
    angkaKedua = ((int)(F * 10) % 10);  //pembulatan angka kedua

    if ((angkaPertama % 2 == angkaKedua % 2)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}