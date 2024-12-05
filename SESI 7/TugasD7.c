#include <stdio.h>

int main() {
    int N, M, Q;
    scanf("%d %d %d", &N, &M, &Q);

    int arr[100][100] = {0};

    for(int i = 0; i < Q; i++) {
        int X, Y, A;
        scanf("%d %d %d", &X, &Y, &A);
        arr[X][Y] = A;
    }   

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            printf("%d", arr[i][j]);
            if(j < M-1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
