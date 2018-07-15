
// *added test code with the sort code. *completed hollyday function. *corrected the code for "Brand" god of fire spawned. * added nice quotes for the status of Lost. * completed the code by adding health status.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define Num_dates 12
int calculatedamagetaken( char*,struct tm*  );
int holly_day( struct tm* );
int invincible_champion(char*  );
int cmp_dates_ascend(const void *d1, const void *d2);
void Lostmessage(void);




int main()
{
   // Test the code by an array of datetimes within 1 hour.
   // char datestring[Num_dates][20] = {"2018-06-13 07:30", "2018-06-13 07:41", "2018-06-13 07:58", "2018-06-13 07:45"};
    //Test the code by an array of datetimes normal.
    char datestring[Num_dates][20] = {"2018-07-13 22:30", "2018-07-13 20:00", "2018-07-13 12:58", "2018-07-13 10:45","2018-07-14 07:45", "2018-07-15 07:45", "2018-07-16 07:45","2018-07-19 07:45","2018-07-13 07:45","2018-07-12 07:45","2018-07-20 07:45","2018-07-22 08:45" };
    
    
    // All type of champions in Gate of Ishtar
    char champions[5][20] ={"Human 100","Giant 150","Vampire 110","Spirit 100","Wizard 100"};
    
    // Initial health of the champions in the order of their place in the array of champions
    int Initialhealth[5]={100,150,110,100,100};
   
   
    // convert the input string datetime array to tm structure format array.
    int i,a;
    struct tm dt[Num_dates];memset((void *) &dt, 0, sizeof(dt));
    for(i=0;i<Num_dates;i++){
    strptime(datestring[i], "%Y-%m-%d %R", &dt[i]);
    }
    
    // Sorting the datetime array ascending
    size_t num_dates = sizeof dt / sizeof *dt;
    qsort(dt, num_dates, sizeof *dt, cmp_dates_ascend);
    // Test if the sorting function works well
    /* char time_buff[70];
     for(i=0;i<num_dates;i++){
        strftime(time_buff, sizeof time_buff, " %c " , &dt[i]);
          puts(time_buff);
     }*/

    

    
    // Asking from the player the type of the champion
    printf(" Select your champion by entering the number from the list:\n ");
    for(i=0;i<=4;i++){printf("(%d: %s) ",i+1,champions[i]);}
    printf("\n");
    scanf("%d",&a);
    a-=1;
    
     double totaldamage = 0 , nextdamage,interval=0,healthstatus;
    // Control the status of the health
    // Calculate the total damage of the champion by entering the gate in input datetimes
    for (i=0;i<num_dates && totaldamage<Initialhealth[a];i++){
      
        nextdamage = calculatedamagetaken(champions[a],&dt[i]);
        //printf("%s , %.2f\n",champions[a], nextdamage);
        if (i!=0) {interval = difftime(mktime(&dt[i]),mktime(&dt[i-1]));}
        if (interval >= 3600 || i==0) totaldamage += nextdamage;
        
    
    }
    healthstatus=Initialhealth[a]-totaldamage;
    if(healthstatus>0){ printf(" The final health status of %s is %.2f.\n ",champions[a], healthstatus);}
    else {printf("\n**************************************** GAME OVER!****************************************\n");Lostmessage();}
            
        
    
    return 0;
}




// Calculate the total damage per each entrance of the Ishtar gate.
int calculatedamagetaken (char* champion, struct tm* date)
{
    if (holly_day(date) || invincible_champion(champion)) return 0;
// "Janna" demon of Wind spawned
    else if (date->tm_hour == 6 && date->tm_min >= 0 && date->tm_min <= 29) return 7;
// "Tiamat" goddess of Oceans spawned
    else if (date->tm_hour == 6 && date->tm_min >= 30 && date->tm_min <= 59) return 18;
// "Mithra" goddess of sun spawned
    else if (date->tm_hour == 7 && date->tm_min >= 0 && date->tm_min <= 59) return 25;
// "Warwick" God of war spawned
    else if (date->tm_hour == 8  && date->tm_min >= 0 && date->tm_min <= 29) return 18;
// "Kalista" demon of agony spawned
    else if (date->tm_hour >= 8 && date->tm_hour <= 14 && date->tm_min >= 30 && date->tm_min <= 59) return 7;
// "Ahri" goddess of wisdom spawned
    else if (date->tm_hour == 15 && date->tm_min >= 0 && date->tm_min <= 29) return 13;
// "Brand" god of fire spawned
    else if ((date->tm_hour == 15 && date->tm_min >= 30) || (date->tm_hour == 16 && date->tm_min <= 59))
    return 25;
// "Rumble" god of lightning spawned
    else if (date->tm_hour == 17 && date->tm_min >= 0 && date->tm_min <= 59)
    return 18;
// "Skarner" the scorpion demon spawned
    else if (date->tm_hour >= 18 && date->tm_hour <= 19 && date->tm_min >= 0 && date->tm_min <= 59)
    return 7;
// "Luna" The goddess of the moon spawned
    else if (date->tm_hour == 20 && date->tm_min <=59) return 13;
    else return 0;
    }

// chech the date whether it is a safe date (holly day).
int holly_day(struct tm* date){
    if(date->tm_wday==2 || date->tm_wday==4) return 1;
        else return 0;
}

// check the status of the champion including whether it is a magical champion or not.
int invincible_champion(char *champion)
{
    if (strcmp(champion,"Wizard 100")==0 || strcmp(champion,"Spirit 100")==0) {return 1;}
    else if ( strcmp(champion,"Human 100")==0 || strcmp(champion,"Giant 150")==0 || strcmp(champion,"Vampire 110")==0) {return 0;}
    else  {printf("Error: The champion is not included in the list.\n"); exit(0);}
   
    }
// comparison of two date-time inorder to sort the datestring array in ascending order.
int cmp_dates_ascend(const void *d1, const void *d2)
{
    struct tm *date_1 = (struct tm *) d1;
    struct tm *date_2 = (struct tm *) d2;
    double d;
    return  d = difftime(timegm(date_1), timegm(date_2));
}

// Quotes appearing on the screen when the player loses the game.
void Lostmessage(void)
{
    char quotes[10][400]=
    { " !!!Yesterday is not ours to recover, but tomorrow is ours to win or lose.!!! Lyndon B. Johnson",
        " !!!You learn more from losing than winning. You learn how to keep going.!!! Morgan Wootten",
        " !!!True champions aren't the ones who always win, but those with the most guts.!!! Mia Hamm",
        " !!!Sometimes by losing a battle, you find a new way to win the war.!!! Donald Trump",
        " !!!To be a champion, I think you have to see the big picture. It's not about winning and losing; it's about every day hard work and about thriving on a challenge. It's about embracing the pain that you'll experience at the end of a race and not be afraid.!!! Summer Sanders",
        " !!!First, accept sadness. Realize that without losing, winning isn't so great.!!! Alyssa Milano",
        " !!!Being brave means to know something is scary, difficult, and dangerous, and doing it anyway, because the possibility of winning the fight is worth the chance of losing it.!!! Emilie Autumn",
        " !!!My comeback was not about winning or losing; it was about the feeling of being able to compete at the top level again.!!! Thomas Muster",
        " !!!There is a fine balance between honoring the past and losing yourself in it. For example, you can acknowledge and learn from the mistakes you made, and then move on and refocus on the now. It is called forgiving yourself.!!! Eckhart Tolle",
        " !!!It's okay to lose. Losing teaches you something. Having to try and go through the trials and tribulations to actually overcome, to get there to win, to triumph, that's what makes life interesting.!!! Elizabeth Banks"};
    
    
    char random[400];
   
    srand((unsigned) clock());
   int  a=rand() % 10;
    strcpy(random ,quotes[a]);
    printf(" %s\n",random);
    printf("******************************************************************************************\n\n");
}

