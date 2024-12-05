#include <stdio.h>
#include <string.h>


int main (void){

int T;
int N;
long long int K;
char S[100];

    scanf ("%d", &T);
    for (int i = 1; i <= T; i++){
        scanf ("%d %lld", &N, &K);
        scanf ("%s", S);


        for (int j = 0; j < N; j++){
            int string_awal = S[j] -'a';
            int string_baru = (string_awal + K) % 26;
            S[j] = 'a' + string_baru;

        }

        printf ("Case #%d: %s\n", i, S);
    }

return 0;

}