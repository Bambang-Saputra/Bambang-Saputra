#include <stdio.h>

int main(void) {
    int T;
    long long int N, M, NilaiNM;

    scanf("%d", &T);

    for (int i = 1; i <= T; i++) {
        scanf("%lld %lld", &N, &M);

        NilaiNM = N * M;
        if (NilaiNM % 2 == 0) {
            printf("Case #%d: Party time!\n", i);
        } else {
            printf("Case #%d: Need more frogs\n", i);
        }
    }

    return 0;
}
