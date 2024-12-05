#include <stdio.h>

int main (void){
    int T;
    int N;

    scanf ("%d", &T);
    for (int i = 1; i <= T; i++){
        scanf ("%d", &N);
        

        int ARRAY[1000][1000] = {0}; 
        for (int j = 0; j < N; j++){
            for (int k = 0 ; k < N; k++) {
                scanf ("%d", &ARRAY[j][k]);
            }
        }
        int columnSum[1000] = {0};
        
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) { 
                columnSum[k] += ARRAY[j][k];
            }
        }

     
        printf("Case #%d: ", i);
        for (int j = 0; j < N; j++) {
            printf("%d", columnSum[j]);
            if (j < N - 1) {
                printf(" "); 
            }
        }
        printf("\n"); 
    }

    return 0;
}