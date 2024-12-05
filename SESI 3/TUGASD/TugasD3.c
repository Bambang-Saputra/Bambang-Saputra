#include <stdio.h>

int main (void){
    char pelajaran[10];
    int hourstart,minutestart,hourend,minuteend;
    int i;
    char sch[4][100];

    for (i=0; i<5; i++){
        scanf("%s %d:%d-%d:%d", &pelajaran, &hourstart, &minutestart, &hourend, &minuteend);
        getchar();

        if (hourstart >= 8 && hourend <=20)
            {
            hourstart -= 1 ;
            hourend -= 1 ;
            }
    sprintf (sch[i], "%s %02d:%02d-%02d:%02d", pelajaran, hourstart, minutestart, hourend, minuteend);
    }
    for (i=0; i<5; i++){
        printf ("%s\n", sch[i]);
    }
    return 0;
}