#include <stdio.h>

int food = 0;  // Variabel global untuk menghitung jumlah makanan yang ditemukan

// Fungsi rekursif untuk mengeksplorasi peta dan menghitung makanan yang ditemukan
void checkMap(char map[][101], int visited[][101], int x, int y, int j, int k) {
    // Cek apakah posisi (j, k) berada di luar peta atau sudah dikunjungi atau merupakan tembok
    if(j < 0 || j >= x || k < 0 || k >= y || visited[j][k] || map[j][k] == '#') {
        return;  // Jika kondisi tidak valid, keluar dari fungsi
    }

    // Tandai posisi (j, k) sebagai sudah dikunjungi
    visited[j][k] = 1;

    // Jika posisi mengandung makanan ('*'), hitung dan ganti dengan '.'
    if(map[j][k] == '*') {
        food++;  // Tambah jumlah makanan yang ditemukan
        map[j][k] = '.';  // Ganti makanan dengan titik (sudah diambil)
    }

    // Lakukan rekursi untuk mengeksplorasi posisi sekeliling (atas, bawah, kiri, kanan)
    checkMap(map, visited, x, y, j + 1, k);  // Eksplorasi ke bawah
    checkMap(map, visited, x, y, j - 1, k);  // Eksplorasi ke atas
    checkMap(map, visited, x, y, j, k + 1);  // Eksplorasi ke kanan
    checkMap(map, visited, x, y, j, k - 1);  // Eksplorasi ke kiri
}

int main() {
    int t;  // Jumlah kasus uji
    scanf("%d", &t);  // Membaca jumlah kasus uji

    // Proses setiap kasus uji
    for (int i = 1; i <= t; i++) {
        int x, y;  // Ukuran peta (x = baris, y = kolom)
        scanf("%d %d", &x, &y);  // Membaca ukuran peta

        int px, py;  // Posisi pemain (P)
        char map[101][101];  // Peta yang berukuran maksimum 101x101
        int visited[101][101] = {0};  // Matriks untuk menandai posisi yang sudah dikunjungi

        // Membaca peta dan menemukan posisi pemain (P)
        for (int j = 0; j < x; j++) {
            for (int k = 0; k < y; k++) {
                scanf(" %c", &map[j][k]);  // Membaca karakter peta

                if (map[j][k] == 'P') {
                    px = j;  // Menyimpan baris posisi pemain
                    py = k;  // Menyimpan kolom posisi pemain
                }
            }
        }

        // Reset jumlah makanan yang ditemukan sebelum memulai pengeksploran
        food = 0;

        // Panggil fungsi rekursif untuk mengeksplorasi peta dari posisi pemain
        checkMap(map, visited, x, y, px, py);

        // Cetak hasil untuk kasus uji ke-i
        printf("Case #%d: %d\n", i, food);
    }

    return 0;  // Mengakhiri program
}
