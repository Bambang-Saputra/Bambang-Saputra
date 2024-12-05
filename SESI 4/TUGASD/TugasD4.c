#include <stdio.h>

int main (void){
	int T, x, y, z;
	int BanyakAnak;
	int KepunyaanCoklat;
	long long int CoklatTerbanyak = 0;
	long long int CoklatTerbanyakTiapAnak = 0;
	long long int CoklatAnak ;
	
	scanf ("%d", &T);
	for (x = 0 ;  x < T; x++){
		CoklatTerbanyak = 0;
		scanf ("%d %d", &BanyakAnak, &KepunyaanCoklat);
		
		for (y = 1; y <= BanyakAnak; y++){
		CoklatTerbanyakTiapAnak = 0;
		
			for (z = 1; z <= KepunyaanCoklat; z++){
				scanf ("%lld", &CoklatAnak);
				
				if (CoklatAnak > CoklatTerbanyakTiapAnak){
					CoklatTerbanyakTiapAnak = CoklatAnak;
				}
				
			}
			CoklatTerbanyak += CoklatTerbanyakTiapAnak;
		}
		
		printf ("Case #%d: %lld\n", x + 1, CoklatTerbanyak);
	}
	
	return 0;
}