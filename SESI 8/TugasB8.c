#include <stdio.h>

//recursion jobonacci
int jobonacci(int n){
    if(n == 0) {
        return 0;
    }
    if(n == 1){
        return 1;
    }
    if(n == 2){
        return 1;
    }
    // Fungsi ini bertujuan karena rekursif baru bisa berjalan ketika n >= 3
    return jobonacci(n-1)+ jobonacci(n-3);
}

int main (void){
    int n;
    scanf ("%d", &n);
    int result = jobonacci(n);
    printf("%d\n", result);

return 0;
}