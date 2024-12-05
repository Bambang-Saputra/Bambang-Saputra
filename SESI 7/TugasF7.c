#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 1) {
        printf("1\n");
        return 0;
    } else if (n == 2) {
        printf("2\n");
        return 0;
    }
    
    int prev2 = 1, prev1 = 2, current = 0;

    for (int i = 3; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    printf("%d\n", current);
    return 0;
}