#include <stdio.h>

int main (void){
	int liftx, lifty, liftk;
	int t;
	
	scanf ("%d %d %d", &liftx, &lifty, &liftk);
	for (t = 0 ; t < 100; t++){
	int posisiliftx = liftx + t;
	int posisilifty = lifty - t;
	if (posisiliftx == liftk && posisilifty == liftk) {
            printf("%d\n", t); 
            return 0;          
        }
    }

    printf("-1\n");
    return 0;
}