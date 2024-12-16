#include <stdio.h>
#include <string.h>

void encryption(char word[], char key[], int length){
    for(int i=0; i<length; i++){
        int x = (int) word[i];
        int y = (int) key[i];
        char result = (char)((x*y%26)+65);
        word[i] = result;
    }
}

int check(char word[], int length){
    int count=0;
    for(int i=0; i<length; i++){
        int x = (int) word[i];
        if(!((x>=65 && x<=90)||(x>=97 && x<=122))){
            count++;
        }
    }
    if(count>0){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    int T;
    scanf("%d", &T);
    char word[T][101];
    char key[T][101];
    for(int i=0; i<T; i++){
        scanf("%s %s", word[i], key[i]);
    }
    for(int i=0; i<T; i++){
        int length = strlen(word[i]);
        if(length==strlen(key[i]) && check(word[i], length)==0 && check(key[i], length)==0){
            encryption(word[i], key[i], length);
            printf("%s\n", word[i]);
        }else{
            printf("ERROR\n");
        }
    }

    return 0;
}