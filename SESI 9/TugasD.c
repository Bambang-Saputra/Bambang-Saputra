#include <stdio.h>

int MATHEMATICS(long long int x, long long int y, long long int z) {
    if (x + y == z || x + z == y || y + z == x) {
        return 1;
    }
    if (x - y == z || x - z == y || y - z == x || y - x == z || z - x == y || z - y == x) {
        return 1;
    }
    if (x * y == z || x * z == y || y * z == x) {
        return 1;
    }
    if (y != 0 && x / y == z || x != 0 && y / x == z || z != 0 && x / z == y || y != 0 && z / y == x) {
        return 1;
    }

    return 0;
}

int main(void) {
    int t;
    long long int x, y, z;
    scanf("%d", &t);

    while (t--) {
        scanf("%lld %lld %lld", &x, &y, &z);
        
        if (MATHEMATICS(x, y, z)) {
            printf("POSSIBLE\n");
        } else {
            printf("IMPOSSIBLE\n"); 
        }
    }
    return 0;
}
