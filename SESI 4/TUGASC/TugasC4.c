#include <stdio.h>

int main(void) {
    int N, M, i;
    long int max_bibi, max_naga;
    scanf("%d %d", &N, &M); 

    int bibi[N], naga[M]; 

    for (i = 0; i < N; i++) {
        scanf("%d", &bibi[i]);
    }


    for (i = 0; i < M; i++) {
        scanf("%d", &naga[i]);
    }

    //menggunakakn bibi[0] karena kita sudah berasumsi bahwa user telah menginput berbagai data
    max_bibi = bibi[0];
     // menggunakan i=1 karena kita sudah menetapkan perbandingan awal dengan i[0]
    for (i = 1; i < N; i++) {
        if (bibi[i] > max_bibi) {
            max_bibi = bibi[i];
        }
    }

    max_naga = naga[0];
    // menggunakan i=1 karena kita sudah menetapkan perbandingan awal dengan i[0]
    for (i = 1; i < M; i++) {
        if (naga[i] > max_naga) {
            max_naga = naga[i];
        }
    }

    if (max_bibi > max_naga) {
        printf("The dark secret was true\n");
    } else {
        printf("Secret debunked\n");
    }

    return 0;
}