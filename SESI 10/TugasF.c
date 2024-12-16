#include <stdio.h>
#include <string.h>

void simulate_rewindatron() {
    int T;
    scanf("%d", &T);
    
    if (T < 1 || T > 7200) {
        printf("Invalid time input. T must be between 1 and 7200.\n");
        return;
    }
    
    int success = 0;
    char S[101];
    while (T > 0) {
        if (scanf("%100s", S) == EOF) {
            break;
        }
        
        if (strcmp(S, "wobble") == 0) {
            scanf("%100s", S);
            if (strcmp(S, "waffle") == 0) {
                success = 1;
                break;
            }
        } 
        
        T -= 30;
    }
    
    if (success) {
        printf("Meshui Returned Back to Normal.\n");
    } else {
        printf("May Chaos Take the World!\n");
    }
}

int main() {
    simulate_rewindatron();
    return 0;
}

