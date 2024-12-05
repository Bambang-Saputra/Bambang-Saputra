#include <stdio.h>

// Fungsi untuk mencetak deret Fibonacci dengan aturan khusus
int cetakFibonacci(int n) {
    int prev2 = 1, prev1 = 10;
    int current;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("0 "); // Indeks ke-0 selalu 0
        } else if (i == 1 || i == 2) {
            printf("1 "); // Indeks ke-1 dan ke-2 selalu 1
        } else if (i == 3 ) {
            printf("10 "); // Indeks ke-3 akan selalu bernilai 10
        } else if ((i) % 3 == 0) {
            // Indeks kelipatan 3 bernilai 10
            printf("10 ");
            prev2 = prev1; // Perbarui nilai sebelumnya untuk melanjutkan perhitungan
            prev1 = 10;    // Tetapkan nilai prev1 ke 10
        } else {
            // Hitung bilangan Fibonacci
            current = prev1 + prev2;
            printf("%d ", current);
            prev2 = prev1; // Perbarui nilai sebelumnya
            prev1 = current;
        }
    }
    printf("\n"); // Baris baru setelah output selesai
}

int main(void) {
    int n;
    scanf("%d", &n); // Input jumlah elemen deret Fibonacci
    cetakFibonacci(n); // Cetak deret Fibonacci
    return 0;
}
