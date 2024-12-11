#include<stdio.h>
#include<string.h>

struct Plant{
    int num;
    char nama[41];
};

int baca(struct Plant plant[1000]){
    int n;
    FILE *fp = fopen("testdata.in", "r");

    if(fp == NULL){
        printf("data not found\n");
    }else{
        fscanf(fp, "%d\n", &n);
        for(int i=0 ; i<n; i++){
            fscanf(fp, "%d#%[^\n]\n", &plant[i].num, plant[i].nama);
        }    
        fclose(fp);
    }
    return n;
}

void cetak(struct Plant plant[1000], int n){
    for(int i=0; i<n; i++){
        printf("%d %s\n", plant[i].num, plant[i].nama);
    }
}

void bubbleSort(struct Plant plant[1000], int a){
    for(int i=0; i<a-1; i++){
        for(int j=0; j<a-i-1; j++){
            if(strcmp(plant[j].nama, plant[j+1].nama) > 0){
                struct Plant temp =  plant[j];
                plant[j] = plant[j+1];
                plant[j+1] =  temp;
            }
        }
    }
}

int main(){
   struct Plant plant[1000];
    int n = baca(plant);

    bubbleSort(plant, n);
    cetak(plant, n);

    return 0;
}