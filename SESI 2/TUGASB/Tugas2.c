#include <stdio.h>

int main (void){

    unsigned int N;
    unsigned int hasil = 1;
    unsigned Kemungkinan;

    scanf ("%d", &N);
  
    for (int i = 0; i < N; i++){
        hasil *= 2;
    }

    Kemungkinan = hasil-1;

    printf ("%d\n", Kemungkinan);
    return 0;
}