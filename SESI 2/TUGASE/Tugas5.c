#include <stdio.h>

int main(void) {
    int T;
    int C; 
    float R, F, K;


    scanf("%d", &T);


    for (int i = 0; i < T; i++) {
        scanf("%d", &C);


        R = (4.0 / 5.0) * C; 
        F = (9.0 / 5.0) * C + 32; 
        K = C + 273.0;

        printf("%.2f %.2f %.2f\n", R, F, K);
    }

    return 0;
}