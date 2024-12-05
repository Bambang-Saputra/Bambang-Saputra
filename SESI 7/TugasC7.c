#include <stdio.h>

int main (void){
    int x;
    long long int z;

    scanf ("%d", &x);
    for (int i = 1; i <= x; i++){
        long long int z;
        scanf ("%lld", &z);

        long long int y[z];
            for (int j = 0 ; j < z; j++){
                scanf("%lld", &y[j]);
            }

            long long int max1=y[0], max2=-1;

            for(int j=1; j<z;j++){
                    if(y[j] >= max1){
                        max2 = max1;
                        max1 = y[j];
                    }else if(y[j] > max2){
                        max2 = y[j];
                    }
            }
		long long int total = max1 + max2;
		printf("Case #%d: %lld\n", i, total);
	}
	return 0;
}