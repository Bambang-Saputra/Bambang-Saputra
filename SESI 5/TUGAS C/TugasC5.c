#include <stdio.h>
#include <string.h>

int main (void){
    int T;
    char S[1001];

    scanf ("%d", &T);
    for (int i = 1 ; i <= T; i++){
        scanf ("%s", S);

        int len = strlen(S);

        printf ("Case #%d : ", i);
        for (int j = len - 1 ; j >= 0  ; j--){
            printf ("%c", S[j]);
        }
        printf("\n");
    }
return 0 ;
}

