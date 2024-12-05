#include <stdio.h>

int main(void){
    int T;
    long long int N;


    scanf ("%d", &T);
    for (int i=1; i <= T; i++){
        scanf ("%lld", &N);
        
            int output = 0;
            for (long long int X = 1; X * X <= N; X++) { // Loop hingga akar kuadrat N
                if (N % X == 0) { // Jika X adalah faktor N
                    output++; // Hitung X sebagai faktor
                    if (X != N / X) { // Jika pasangan faktor berbeda
                        output++; // Hitung pasangan faktor
                    }
                }
            }
        printf("Case #%d: %d\n", i, output);
    }
                
return 0;
}