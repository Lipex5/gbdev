#include <gb/gb.h>

#include "stdio.h"

#define MAX_SPRITES 40

#define NR_PLAYER_UNITS 10
#define MAX_SPEED 5
#define SPAWN_COOLDOWN 2

// Unit Strcuts

// int CastleHP = 200;

// Player units
typedef struct {
    // Stats
    uint8_t tileID;
    uint8_t x;
    uint8_t y;
    int hp;
    int dmg;
    int atkspd;
    int speed;      // Max 5
    uint8_t range;
 // uint8_t cost;
    
    //Other Vats
    uint8_t frame_counter;
    uint8_t alive;

    // Program Vars
    uint8_t spriteID;
} Unit;

// Enemies
typedef struct {
    uint8_t x;
    uint8_t y;
    int hp;
    int dmg;
    int atkspd;
    int spd;
    uint8_t range;
 // uint8_t firstwave;
} Enemy;

// Classes init
/*Unit Soldier =  {
                    1,      // Tile ID
                    50,     // X position
                    50,     // Y position
                    100,    // HP
                    25,     // DMG
                    1,      // Atk Spd
                    1,      // Speed
                    1       // Range
                };*/




// Functions
void spawn_unit(Unit *unit, Unit *unit_group);
void move_unit(Unit *unit);