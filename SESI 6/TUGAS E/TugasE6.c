#include <stdio.h>
int main(){
	int t;

    long long int a,b;
	scanf("%d", &t);
	
	for(int i=1; i<=t; i++){
		scanf("%lld %lld",&a, &b);
		
		long long int digA,digB;
		long long int sum;
		long long int total=0;
		int bantuanDigitBelakangNol=1;
		
		while(a>0 || b>0){
			digA = a%10;
			digB = b%10;
			
			sum=digA+digB;
			if(sum>=10){
				sum-=10;
			}
			
			total += sum*bantuanDigitBelakangNol;
			a/=10;
			b/=10;
			bantuanDigitBelakangNol*=10;
			
		}
		
		printf("Case #%d: %lld\n", i, total);
	}	
}
