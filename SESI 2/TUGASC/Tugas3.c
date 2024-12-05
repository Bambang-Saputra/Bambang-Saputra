#include <stdio.h>

int main (void){
    int Ph, M, Pu;
    float Hasil ;

    scanf ("%d %d %d", &Ph, &M, &Pu);
    Hasil = 0.2 * Ph + 0.3 * M + 0.5 * Pu ;
    printf ("%.2f\n", Hasil);
    return 0;

}
