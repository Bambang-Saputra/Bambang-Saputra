#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void permutasi(int n, int arr[], int index, int results[][6], int *count) {
    if (index == n) {
        // Salin permutasi ke results
        for (int i = 0; i < n; i++) {
            results[*count][i] = arr[i];
        }
        (*count)++;
        return;
    }

    for (int i = index; i < n; i++) {
        // Tukar elemen
        int temp = arr[index];
        arr[index] = arr[i];
        arr[i] = temp;

        // Rekursi untuk elemen selanjutnya
        permutasi(n, arr, index + 1, results, count);

        // Kembalikan posisi elemen seperti semula
        temp = arr[index];
        arr[index] = arr[i];
        arr[i] = temp;
    }
}

int compare(const void *a, const void *b) {
    const int *rowA = (const int *)a;
    const int *rowB = (const int *)b;

    // Bandingkan elemen satu per satu
    for (int i = 0; i < 6; i++) { // Pastikan 6 diganti sesuai dengan n
        if (rowA[i] < rowB[i]) {
            return -1; 
        } else if (rowA[i] > rowB[i]) {
            return 1; 
        }
    }
    return 0;
}

int main (void){

    int n;

    while(1){
        scanf ("%d", &n);
        if (n >= 1 && n <= 6){
            break;
        }
    }
    int arr[n];

    for (int i = 0; i < n; i++){
        while(1){
            scanf ("%d", &arr[i]);
            if (arr[i] >= 0 && arr[i] <= 9){
                break;
            }
        }
    }

    int results[720][6] = {0}; // 6! = 720 (maksimal permutasi)
    int count = 0;

    // Panggil fungsi permutasi
    permutasi(n, arr, 0, results, &count);

    // Sorting hasil permutasi
    qsort(results, count, sizeof(results[0]), compare);

    // Mencetak hasil permutasi
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", results[i][j]);
        }
        printf("\n");
    }

    return 0;
}
