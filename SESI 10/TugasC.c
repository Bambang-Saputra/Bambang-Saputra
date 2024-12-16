#include <stdio.h>
#include <math.h>

int main() {
    FILE *file = fopen("testdata.in", "r");
    if (!file) {
        printf("Error: File tidak ditemukan!\n");
        return 1;
    }

    int T; 
    fscanf(file, "%d", &T);

    for (int t = 1; t <= T; t++) {
        int N, M;
        fscanf(file, "%d %d", &N, &M);

        int size = N * M;
        int count[256] = {0}; 

        for (int i = 0; i < size; i++) {
            int pixel;
            fscanf(file, "%d", &pixel);
            count[pixel]++;
        }

        int median;
        int cumulative = 0;
        for (int i = 0; i < 256; i++) {
            cumulative += count[i];
            if (cumulative >= (size + 1) / 2) { 
                if (size % 2 == 1 || cumulative > (size / 2)) {
                    median = i;
                } else {
                    for (int j = i + 1; j < 256; j++) {
                        if (count[j] > 0) {
                            median = round((i + j) / 2.0);
                            break;
                        }
                    }
                }
                break;
            }
        }

        printf("Case #%d: %d\n", t, median);
    }

    fclose(file);
    return 0;
}