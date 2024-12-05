#include <stdio.h>

int main (void){

    int T = 3;
    int a, b, c, d;
    double hasil;

    for (int i = 0; i<T; i++){
        scanf ("%d %d %d %d", &a, &b, &c, &d);
        
        hasil = a + b + c + d;

        printf ("%.2lf\n", hasil);
        
    }

    return 0;
}