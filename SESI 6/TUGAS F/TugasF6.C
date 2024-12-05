#include <stdio.h>

int main() {
    int count;
    scanf("%d", &count);
    int numbers[count];
    getchar();

    for (int i = 0; i < count; i++) {
        scanf("%d", &numbers[i]);
    }

    int maxVal = -1000000;
    int minVal = 1000000;

    for (int i = 0; i < count; i++) {
        if (numbers[i] > maxVal) {
            maxVal = numbers[i];
        }
        if (numbers[i] < minVal) {
            minVal = numbers[i];
        }
    }

    int total = 0;
    for (int i = 0; i < count; i++) {
        if (numbers[i] != minVal && numbers[i] != maxVal) {
            total += numbers[i];
        }
    }

    printf("FiddleSum: %d\n", total);
    return 0;
}