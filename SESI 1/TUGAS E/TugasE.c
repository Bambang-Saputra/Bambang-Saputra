#include <stdio.h>

int main (void){
    char N[100];
    int NIS, U;
    scanf ("%[^\n]", N); 
    getchar();
    scanf ("%d %d", &NIS, &U);
    printf ("Name: %s\n", N);
    printf ("NIS: %d\n", NIS);
    printf ("Age: %d\n", U);

    return 0;
}