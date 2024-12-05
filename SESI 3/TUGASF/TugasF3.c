#include <stdio.h>

int main (void){
    int nomor, reversed = 0, remainder;

    scanf ("%d", &nomor);
    
    while (nomor!= 0){
        remainder = nomor % 10;
        reversed = reversed * 10 + remainder;
        nomor /= 10;
    }

    printf("%d\n", reversed);

    return 0;
}