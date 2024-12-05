#include <stdio.h>
int main(){
	int t,n;
	scanf("%d", &t);
	
	for(int i=1; i<=t; i++){
		scanf("%d", &n);
		
		int skor[1000];
		for(int j=1; j<=n;j++){
			scanf("%d", &skor[j]);
		}
		
		int bibi, lili;
		scanf("%d %d", &bibi, &lili);
		
		if(bibi != lili){
			if(skor[bibi] > skor[lili]){
			printf("Case #%d : Bibi\n",i);
			}else if(skor[bibi] == skor[lili]){
				printf("Case #%d : Draw\n",i);
			}else{
				printf("Case #%d : Lili\n",i);
			}
		}
		
	}
	return 0;
}
