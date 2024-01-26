#include "Defines.h"
#include <stdbool.h>

#define MAX_PISTOLS 2
#define MAX_PLAYERS 2
#define GLOCK_ARMOR_DAMAGE 2
#define DESERT_EAGLE_ARMOR_DAMAGE 0.25
#define DESERT_EAGLE_HEALTH_DAMAGE 0.75
#define GLOCK_SHOTS 3

struct PlayerVitalData;

typedef struct Pistol
{
    int pistolType;
    int damagePerRound;
    int clipSize;
    int currClipBullets;
    int remainingAmmo;
}Pistol;

typedef struct PlayerVitalData
{
    Pistol pistol;
    int health;
    int armor;
    void (*fire)(struct PlayerVitalData *,struct PlayerVitalData *);
}PlayerVitalData;

void fire(PlayerVitalData *attacker, PlayerVitalData *defender);

void playerInit (PlayerVitalData *player, int health, int armor);
void pistolInit(PlayerVitalData *player, int type, int damagePerRound, int clipSize, int remainingAmmo);

bool isDead(PlayerVitalData *player);

bool processPlayer1Turn(PlayerVitalData *player1, PlayerVitalData *player2);
bool processPlayer2Turn(PlayerVitalData *player2, PlayerVitalData *player1);

void startFight(PlayerVitalData *player1, PlayerVitalData *player2);
