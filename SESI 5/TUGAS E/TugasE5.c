#include <stdio.h>
#include <string.h>

int main (void){
    int T;
    char S[1000];

    scanf ("%d", &T);
    for (int i = 1; i <= T; i++){
        scanf ("%s", S);

        int len = strlen (S);
    
    int isPalindrome(int start, int end) {

            if (start >= end) {
                return 1; 
            }

            if (S[start] != S[end]) {
                return 0; 
            }

            return isPalindrome(start + 1, end - 1);
        }

        if (isPalindrome(0, len - 1)) {
            printf("Case #%d: yes\n", i);
        } else {
            printf("Case #%d: no\n", i);
        }
    }

return 0;
}