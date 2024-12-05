#include <stdio.h>
int main()
{
    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; i++)
    {
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);

        // pattern
        int pattern[50][50];
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                scanf("%d", &pattern[j][k]);
            }
        }

        // friends number
        int roomCon[1][50] = {0};
        int num;
        for (int j = 0; j < q; j++)
        {
            scanf("%d", &num);

            // room visiting
            for (int k = 0; k < m; k++)
            { 
                if(roomCon[0][k] == 0 && pattern[num-1][k] == 0){
                    roomCon[0][k] = 0;
                }else if(roomCon[0][k] == 0 && pattern[num-1][k] == 1){
                    roomCon[0][k] = 1;
                }else if(roomCon[0][k] == 1 && pattern[num-1][k] == 0){
                    roomCon[0][k] = 1;
                }else if(roomCon[0][k] == 1 && pattern[num-1][k] == 1){
                    roomCon[0][k] = 0;
                }
            }
        }

        //print
        printf("Case #%d:\n", i);
        for (int j = 0; j < m; j++){
            if(roomCon[0][j] == 1){
                printf("YES\n");
            }else {
                printf("NO\n");
            }
        }
    }
    return 0;
}