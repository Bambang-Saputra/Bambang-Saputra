#include <stdio.h>
#include <string.h>

int main (void){
    int A;
    char S[1000000];

    scanf ("%d", &A);
    for (int i = 1 ; i <= A; i++){
        scanf ("%s", &S);
        int panjang = strlen (S);

    int total[1000] = {0};
		int totalHuruf = 0;
		for(int j=0; j<panjang; j++){
			int n = S[j];
			if(n>='a' && n<='z'){
				if(total[n]==0){
					total[n]+=1;
					totalHuruf+=1;
				}
			}
		}
		
		if(totalHuruf%2 == 0){
			printf("Case #%d: Yay\n",i);
		}else{
			printf("Case #%d: Ewwww\n",i);
		}
		
		
	}
	return 0;
}

