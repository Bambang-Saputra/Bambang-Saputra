#include <stdio.h>

int main (void){
    long long int a,b,c,d,e,f,g,h,i,j,k,l;
    long long int hitung1, hitung2, hitung3;

    getchar(); // untuk kurung buka
    scanf("%lld", &a);
    getchar(); // untuk +
    scanf("%lld", &b);
    getchar(); // untuk kurung tutup
    getchar(); // untuk kali
    getchar(); // untuk kurung buka
    scanf("%lld", &c);
    getchar(); // untuk -
    scanf("%lld", &d);
    getchar(); // untuk kurung tutup
    getchar();
    hitung1 = (a+b)*(c-d);

    getchar(); // untuk kurung buka
    scanf("%lld", &e);
    getchar(); // untuk +
    scanf("%lld", &f);
    getchar(); // untuk kurung tutup
    getchar(); // untuk kali
    getchar(); // untuk kurung buka
    scanf("%lld", &g);
    getchar(); // untuk -
    scanf("%lld", &h);
    getchar(); // untuk kurung tutup
    getchar();
    hitung2 = (e+f)*(g-h);

    getchar(); // untuk kurung buka
    scanf("%lld", &i);
    getchar(); // untuk +
    scanf("%lld", &j);
    getchar(); // untuk kurung tutup
    getchar(); // untuk kali
    getchar(); // untuk kurung buka
    scanf("%lld", &k);
    getchar(); // untuk -
    scanf("%lld", &l);
    getchar(); // untuk kurung tutup
    getchar();
    hitung3 = (i+j)*(k-l);

    printf ("%lld %lld %lld\n", hitung1, hitung2, hitung3);
    return 0;
}