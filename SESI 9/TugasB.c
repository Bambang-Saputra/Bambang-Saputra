#include<stdio.h>
#include <string.h>

void WordSortingAsc(char nama[][100], int t) {

    for (int i = 1 ; i < t; i++ ){ 
        char temp[100];
        strcpy (temp, nama[i]);

        int j = i - 1;

        while(j >= 0 && strcmp(nama[j], temp) > 0) {
            strcpy (nama[j+1], nama[j]);
            j--;
            }
            strcpy (nama[j+1], temp);
        }
}

void WordSortingDes(char nama[][100], int t) {

    for (int i = 1 ; i < t; i++ ){ 
        char temp[100];
        strcpy (temp, nama[i]);

        int j = i - 1;

        while(j >= 0 && strcmp(nama[j], temp) < 0) {
            strcpy (nama[j+1], nama[j]);
            j--;
            }
            strcpy (nama[j+1], temp);
        }
}

int main (void){
    int t;
    int x;
    
    scanf("%d", &t);
    char nama[t][100];
    for(int i = 0; i < t; i++){
        scanf("%s", nama[i]);
    }

    scanf("%d", &x);

    if( x == 0){
        WordSortingAsc(nama, t);
    } else {
        WordSortingDes(nama, t);
    }

    for (int i = 0; i < t; i++){
        printf ("%s\n", nama[i]);
    }

    return 0;
}