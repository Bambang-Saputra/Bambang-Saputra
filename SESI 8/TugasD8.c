#include <stdio.h>

int not_fibonacci(int k, int fibonacci0, int fibonacci1){
    if (k == 0){
        return fibonacci0; //ketika nilai k adalah 0, kita hanya perlu mengambil angka pertama dalam deret
    }
    if (k == 1){
        return fibonacci1; //ketika nilai k adalah 1, kita hanya perlu mengambil angka kedua dalam deret
    }
    return not_fibonacci(k-1,fibonacci0,fibonacci1) + not_fibonacci(k-2,fibonacci0,fibonacci1);
}
int main(void){
    int fibonacci0;
    int fibonacci1;
    int k;

    scanf("%d %d", &fibonacci0, &fibonacci1);
    scanf("%d", &k);

    int result = not_fibonacci(k, fibonacci0, fibonacci1);
    printf("%d\n", result);

    return 0;
}