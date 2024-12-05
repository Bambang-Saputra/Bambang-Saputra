#include <stdio.h>

int main (void){
    int T, Kejadian;
    long long int BotolMadu,BotolKosong;
    long long int TotalMadu, BotolSetelahDiminum;
    long long int MaduBaru;


    scanf ("%d", &T);
    for (Kejadian = 1; Kejadian <= T; Kejadian++){

        scanf ("%lld %lld", &BotolMadu, &BotolKosong);

        TotalMadu = BotolMadu ;
        BotolSetelahDiminum = BotolMadu;

        while (BotolSetelahDiminum >= BotolKosong){
        MaduBaru = BotolSetelahDiminum / BotolKosong;
        TotalMadu += MaduBaru;
        BotolSetelahDiminum = MaduBaru + (BotolSetelahDiminum % BotolKosong);

        }

        printf ("Case #%d: %lld\n", Kejadian, TotalMadu);
    }
    return 0;
}