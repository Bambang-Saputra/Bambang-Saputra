#include <stdio.h>

int main (void){
    int T;
    long long int A,B,C;
    scanf ("%d", &T);

    for (int i = 1; i <= T; i++){
        scanf("%lld %lld %lld", &A, &B, &C);
        int Syarat = A + B;

        if (Syarat > C){
            printf("BISA\n");
        }
        else {
            printf ("TIDAK BISA\n");
        }
        
    }
    return 0;
}