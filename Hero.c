#include "Hero.h"
#include <stdbool.h>
#include <stdio.h>

void fire(PlayerVitalData *attacker, PlayerVitalData *defender)
{
    if (0 < defender->armor && 0 == attacker->pistol.pistolType)
    {
        int armoredDamage = attacker->pistol.damagePerRound / GLOCK_ARMOR_DAMAGE;
        
        defender->armor -= armoredDamage;
        defender->health -= armoredDamage;
    } 
    else if(0 < defender->armor && 1 == attacker->pistol.pistolType)
    {
        int armorDamage = attacker->pistol.damagePerRound * DESERT_EAGLE_ARMOR_DAMAGE;
        int healthDamage = attacker->pistol.damagePerRound * DESERT_EAGLE_HEALTH_DAMAGE;

        defender->armor -= armorDamage;
        defender->health -= healthDamage;
    }
    else
    {
        defender->armor -= attacker->pistol.damagePerRound;
    }
    
    
    if (0 > defender->armor)
    {
        defender->health += defender->armor;
        defender->armor = 0;
    }
}

void playerInit (PlayerVitalData *player, int health, int armor)
{
    player->health = health;
    player->armor = armor;
    player->fire = &fire;
}

void pistolInit(PlayerVitalData *player, int type, int damagePerRound, int clipSize, int remainingAmmo)
{
    player->pistol.pistolType = type;
    player->pistol.damagePerRound = damagePerRound;
    player->pistol.clipSize = clipSize;
    player->pistol.remainingAmmo = remainingAmmo;
    player->pistol.currClipBullets = clipSize;
}

bool isDead(PlayerVitalData *player)
{
    return player->health <= 0;
}

bool processPlayer1Turn(PlayerVitalData *player1, PlayerVitalData *player2)
{
    printf("PlayerID 0 turn:\n");

    if (0 >= player1->pistol.currClipBullets && 0 >= player1->pistol.remainingAmmo)
    {
        printf("No ammo left.\n");

        return false;
    }
    
    
    if (GLOCK == player1->pistol.pistolType)
    {
        for (int i = 0; i < GLOCK_SHOTS; i++)
        {
            if (0 >= player1->pistol.currClipBullets)
            {
                printf("Reloading...\n");

                if (player1->pistol.clipSize > player1->pistol.remainingAmmo)
                {
                    player1->pistol.currClipBullets = player1->pistol.remainingAmmo;
                }
                else
                {
                    player1->pistol.currClipBullets = player1->pistol.clipSize;
                }

                player1->pistol.remainingAmmo -= player1->pistol.clipSize;

                if (0 > player1->pistol.remainingAmmo)
                {
                    player1->pistol.remainingAmmo = 0;
                }
                printf("currClipBullets: %d, remainingAmmo: %d\n", player1->pistol.currClipBullets, player1->pistol.remainingAmmo);
        
        
                return false;  
            }

            player1->fire(player1, player2);
            printf("Enemy left with %d health and %d armor\n", player2->health, player2->armor);
            player1->pistol.currClipBullets--;

            if(isDead(player2))
            {
                return true;
            }
        }
    }
    else if(DESERT_EAGLE == player1->pistol.pistolType)
    {
        if (0 >= player1->pistol.currClipBullets)
        {
            printf("Reloading...\n");

            if (player1->pistol.clipSize > player1->pistol.remainingAmmo)
            {
                player1->pistol.currClipBullets = player1->pistol.remainingAmmo;
            }
            else
            {
                player1->pistol.currClipBullets = player1->pistol.clipSize;
            }

            player1->pistol.remainingAmmo -= player1->pistol.clipSize;

            if (0 > player1->pistol.remainingAmmo)
            {
                player1->pistol.remainingAmmo = 0;
            }

            printf("currClipBullets: %d, remainingAmmo: %d\n", player1->pistol.currClipBullets, player1->pistol.remainingAmmo);
        
        
            return false;  
        }

        player1->fire(player1, player2);
        printf("Enemy left with %d health and %d armor\n", player2->health, player2->armor);
        player1->pistol.currClipBullets--;

        if(isDead(player2))
        {
            return true;
        }
    }
    

    if(isDead(player2))
    {
        return true;
    }

    return false;
}

bool processPlayer2Turn(PlayerVitalData *player2, PlayerVitalData *player1)
{
    printf("PlayerID 1 turn:\n");

    if (0 >= player2->pistol.currClipBullets && 0 >= player2->pistol.remainingAmmo)
    {
        printf("No ammo left.\n");

        return false;
    }
    
    
    if (GLOCK == player2->pistol.pistolType)
    {
        for (int i = 0; i < GLOCK_SHOTS; i++)
        {
            if (0 >= player2->pistol.currClipBullets)
            {
                printf("Reloading...\n");

                if (player2->pistol.clipSize > player2->pistol.remainingAmmo)
                {
                    player2->pistol.currClipBullets = player2->pistol.remainingAmmo;
                }
                else
                {
                    player2->pistol.currClipBullets = player2->pistol.clipSize;
                }

                player2->pistol.remainingAmmo -= player2->pistol.clipSize;

                if (0 > player2->pistol.remainingAmmo)
                {
                    player2->pistol.remainingAmmo = 0;
                }
                printf("currClipBullets: %d, remainingAmmo: %d\n", player2->pistol.currClipBullets, player2->pistol.remainingAmmo);
        
        
                return false;  
            }

            player2->fire(player2, player1);
            printf("Enemy left with %d health and %d armor\n", player1->health, player1->armor);
            player2->pistol.currClipBullets--;

            if(isDead(player1))
            {
                return true;
            }
        }
    }
    else if(DESERT_EAGLE == player2->pistol.pistolType)
    {
        if (0 >= player2->pistol.currClipBullets)
        {
            printf("Reloading...\n");

            if (player2->pistol.clipSize > player2->pistol.remainingAmmo)
            {
                player2->pistol.currClipBullets = player2->pistol.remainingAmmo;
            }
            else
            {
                player2->pistol.currClipBullets = player2->pistol.clipSize;
            }

            player2->pistol.remainingAmmo -= player2->pistol.clipSize;

            if (0 > player2->pistol.remainingAmmo)
            {
                player2->pistol.remainingAmmo = 0;
            }
            printf("currClipBullets: %d, remainingAmmo: %d\n", player2->pistol.currClipBullets, player2->pistol.remainingAmmo);
        
        
            return false;  
        }

        player2->fire(player2, player1);
        printf("Enemy left with %d health and %d armor\n", player1->health, player1->armor);
        player2->pistol.currClipBullets--;

        if(isDead(player1))
        {
            return true;
        }
    }



    if (isDead(player1))
    {
        return true;
    }
    return false;    
}

void startFight(PlayerVitalData *player1, PlayerVitalData *player2)
{       
    while (true)
    {
        if (processPlayer1Turn(player1, player2))
        {
            printf("Player with ID: 0 wins!\n");
            break;
        }
        
        if (processPlayer2Turn(player2, player1))
        {
            printf("Player with ID: 1 wins!\n");
            break;
        }
    } 
}