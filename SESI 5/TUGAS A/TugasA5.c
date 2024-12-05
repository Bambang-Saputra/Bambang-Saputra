#include <stdio.h>

int main(void) {
    int T;
    int N;

    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        scanf("%d", &N);
        printf("Case #%d:\n", i);

        for (int j = 0; j < N; j++) {
            // Mencetak spasi
            for (int k = 0; k < N - j - 1; k++) {
                printf(" ");
            }
            // Mencetak karakter
            for (int k = 0; k <= j; k++) {
                if (N % 2 == 0) {
                    if (k % 2 == 0) {
                        printf("#");
                    } else {
                        printf("*");
                    }
                } else {
                    if (k % 2 == 0) {
                        printf("*");
                    } else {
                        printf("#");
                    }
                }
            }
            printf("\n"); // untuk mencetak baris baru setelah setiap baris segitiga
        }
    }

    return 0;
}
