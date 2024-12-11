#include <stdio.h>
#include <string.h>

#define MAX_STR 10
#define MAX_CASES 100

void insertion_sort(char *arr[], int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            int len1 = strlen(arr[j]), len2 = strlen(key);
            int cmp = 0;

            for (int k = 1; k <= len1 && k <= len2; k++) {
                char char1 = arr[j][len1 - k];
                char char2 = key[len2 - k];
                if (char1 != char2) {
                    cmp = (char1 > char2) ? 1 : -1;
                    break;
                }
            }

            if (cmp == 0) {
                cmp = (len1 > len2) ? 1 : -1;
            }

            if (cmp <= 0) break;

            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    for (int case_no = 1; case_no <= t; case_no++) {
        int n;
        scanf("%d", &n);

        char nama[n][MAX_STR + 1], *ptrs[n];

        for (int i = 0; i < n; i++) {
            scanf("%s", nama[i]);
            ptrs[i] = nama[i];
        }
        insertion_sort(ptrs, n);

        printf("Case #%d:\n", case_no);
        for (int i = 0; i < n; i++) {
            printf("%s\n", ptrs[i]);
        }
        printf("\n"); 
    }

    return 0;
}
