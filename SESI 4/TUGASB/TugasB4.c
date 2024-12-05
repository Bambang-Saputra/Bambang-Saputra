#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int matriks[N][N];  
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matriks[i][j]);
        }
    }

    for (int j = 0; j < N; j++) {   
        for (int i = 0; i < N; i++) {
            printf("%d", matriks[i][j]); 
            if (i < N - 1) {
                printf(" ");
            } 
        }
         printf("\n"); 
   }
    return 0;
}

