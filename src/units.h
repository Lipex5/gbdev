#include <gb/gb.h>

#include <stdlib.h>

#include "stdio.h"

#define MAX_SPRITES 40

#define NR_PLAYER_UNITS 10
#define NR_ENEMY_UNITS 10

#define MAX_SPEED 5
#define ATKSPD_MULT 6
#define SPAWN_COOLDOWN 2

// Unit Strcuts

// int CastleHP = 200;

// Player units
typedef struct {
    uint8_t tileID;
    // Stats
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
    int atkspd_counter;
    uint8_t alive;
    uint8_t newx;
    uint8_t newy;

    // Program Vars
    uint8_t spriteID;
} Unit;

// Enemies
typedef struct {
    uint8_t tileID;
    // Stats
    uint8_t x;
    uint8_t y;
    int hp;
    int dmg;
    int atkspd;
    int speed;
    uint8_t range;
 // uint8_t firstwave;

    // Other Vars
    uint8_t frame_counter;
    int atkspd_counter;
    uint8_t alive;
    uint8_t newx;
    uint8_t newy;

    // Program Vars
    uint8_t spriteID;
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
void spawn_unit(Unit *unit, Unit *unit_group, uint8_t x, uint8_t y);

void move_unit(Unit *unit, int8_t x, int8_t y);
uint8_t get_closest_enemy(Unit *unit, Enemy *enemy_group, uint8_t *returnID);
void atk_enemy(Unit *unit, Enemy *enemy);
void kill_unit (Unit *unit);

void spawn_enemy(Enemy *enemy, Enemy *enemy_group, uint8_t x, uint8_t y);
void move_enemy(Enemy *enemy, int8_t x, int8_t y);
uint8_t get_closest_unit(Enemy *enemy, Unit *unit_group, uint8_t *returnID);
void atk_unit(Enemy *enemy, Unit *unit);
void kill_enemy (Enemy *enemy);
