#include <stdio.h>
#include <math.h>

int main() {

    double attack_power = 10000;
    double cooldown = 1; 
    double cast_time = 60;  
    double aoe = 20; 

    char modifier[3];


    for (int i = 0; i < 5; i++) {
      
        scanf("%2s", modifier);
        
      
        if (modifier[0] == 'A' && modifier[1] == 'P') {
            attack_power *= 1.2; 
            cooldown *= 1.3;      
            cast_time *= 1.15;   
            aoe *= 1.05;        
        }
        else if (modifier[0] == 'C' && modifier[1] == 'D') {
            attack_power *= 0.7;  
            cooldown *= 0.8;      
            cast_time *= 1.15;    
            aoe *= 0.5;           
        }
        else if (modifier[0] == 'C' && modifier[1] == 'T') {
            attack_power *= 0.5;
            cooldown *= 1.0;     
            cast_time *= 0.3;
            aoe *= 0.1;          
        }
        else if (modifier[0] == 'A' && modifier[1] == 'E') {
            attack_power *= 1.05;  
            cooldown *= 1.2;    
            cast_time *= 1.1;    
            aoe *= 1.6;            
        }
        
 
        if (i < 4) {
            getchar(); 
        }
    }


    attack_power = floor(attack_power * 10) / 10;
    cooldown = floor(cooldown * 10) / 10;
    cast_time = floor(cast_time * 10) / 10;
    aoe = floor(aoe * 10) / 10;

    printf("Attack Power = %.1f\n", attack_power);
    printf("Cooldown = %.1f Days\n", cooldown);
    printf("Cast Time = %.1f seconds\n", cast_time);
    printf("AoE = %.1f meters\n", aoe);

    return 0;
}
