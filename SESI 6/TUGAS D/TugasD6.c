#include <stdio.h>

int main (void){
    unsigned int X, Y;

    scanf("%u %u", &X, &Y);
	
    unsigned int arr[100][100];
    for(unsigned int i = 0; i < X; i++){
        for(unsigned int j = 0; j < Y; j++){
            scanf("%u", &arr[i][j]);
        }
    }
	
    unsigned int n;
    scanf("%u", &n);
	
    unsigned int a, b, c;
    for(unsigned int i = 0; i < n; i++){
        scanf("%u %u %u", &a, &b, &c);
        arr[a-1][b-1] = c;	
    }
	
    for(unsigned int i = 0; i < X; i++){
        for(unsigned int j = 0; j < Y; j++){
            printf("%u%c", arr[i][j], ((j == Y - 1) ? '\n' : ' '));
        }
    }

    return 0;
}
