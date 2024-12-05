#include <stdio.h>

int main (void){
    int x;

    scanf("%d", &x);

    int y[100][100];
    for (int i = 0 ; i < x; i++){
        for (int j = 0; j < x; j++){
            scanf ("%d", &y[i][j]);
        }
    }

    int ada = 1;

    for(int i = 0 ; i < x; i++){
        for (int j = 0; j < x; j++){
           for(int k = j+1; k < x; k++){
				if(y[i][j]==y[i][k] || y[j][i]==y[k][i]){
					ada=0;
				}
            }
        }
    }
        if(ada==1){
            printf("Yay\n");
        }else{
            printf("Nay\n");
        }
        
    return 0;
}