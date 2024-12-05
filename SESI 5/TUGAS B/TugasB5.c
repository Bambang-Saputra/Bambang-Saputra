#include <stdio.h>

int main (void){
    int N,Q;


    scanf ("%d", &N);
    int A[N];

        for (int i = 0; i < N; i++){
        scanf ("%d", &A[i]);
        }

        scanf ("%d", &Q);
        for (int j= 1; j <= Q; j++){

        int Ai, Bi;
        scanf ("%d %d", &Ai, &Bi);


        int penjumlahan = 0;
        for(int k = Ai - 1; k < Bi; k++) {
        penjumlahan += A[k];
        }
    printf("Case #%d: %d\n", j, penjumlahan);
    }




    return 0;
}