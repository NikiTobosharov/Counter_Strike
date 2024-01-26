#include <stdio.h>
#include <stdlib.h>

#include "Hero.h"

int main() 
{
   PlayerVitalData players[2];
   int health, armor, type, damagePerRound, clipSize, remainingAmmo;

   for (int i = 0; i < MAX_PLAYERS; i++)
   {
      scanf("%d %d", &health, &armor);
      playerInit(&players[i], health, armor);
   }

   for (int i = 0; i < MAX_PLAYERS; i++)
   {
      scanf("%d %d %d %d", &type, &damagePerRound, &clipSize, &remainingAmmo);
      pistolInit(&players[i] ,type, damagePerRound, clipSize, remainingAmmo);
   }
      
   startFight(&players[0], &players[1]);

}