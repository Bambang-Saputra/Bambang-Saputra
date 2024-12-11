#include <stdio.h>
#include <string.h>

typedef struct {
    int aura;
    char name[256];
} Influencer;

void insertion_sort(Influencer influencers[], int t, int ascending) {
    for (int i = 1; i < t; i++) {
        Influencer key = influencers[i];
        int j = i - 1;

        while (j >= 0 &&
               ((ascending && 
                 (influencers[j].aura > key.aura || 
                 (influencers[j].aura == key.aura && strcmp(influencers[j].name, key.name) > 0))) || 
                (!ascending && 
                 (influencers[j].aura < key.aura || 
                 (influencers[j].aura == key.aura && strcmp(influencers[j].name, key.name) < 0))))) {
            influencers[j + 1] = influencers[j];
            j--;
        }
        influencers[j + 1] = key;
    }
}


void AuraSorting(int t, Influencer influencers[]) {
    int ascending = (t % 2 == 0);
    insertion_sort(influencers, t, ascending);

    for (int i = 0; i < t; i++) {
        printf("%d %s\n", influencers[i].aura, influencers[i].name);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    Influencer influencers[t];

    for (int i = 0; i < t; i++) {
        scanf("%d %255[^\n]", &influencers[i].aura, influencers[i].name);
    }

    AuraSorting(t, influencers);

    return 0;
}
