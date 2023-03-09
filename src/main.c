#include <gb/gb.h>

#include <stdint.h>
#include <stdlib.h>
// #include <stdio.h>


#include "../res/sprites.h"
#include "../res/tiles.h"
#include "../res/map.h"
#include "../res/test.h"
#include "units.h"

#define RANGE_UNIT 8

// Global Vars
Unit player_units[NR_PLAYER_UNITS] = {{0}};
Enemy enemy_units[NR_ENEMY_UNITS] = {{0}};

uint8_t prev_input, curr_input = 0;

// Test Vars
uint8_t x = 55;
uint8_t y = 100;

Unit Soldier = {
    1,   // Tile ID
    50,  // X position
    50,  // Y position
    100, // HP
    25,  // DMG
    10,   // Atk Spd
    1,   // Spd
    1,   // Range
    0,
    0,
    0};

Unit Archer = {
    2,   // Tile ID
    70,  // X position
    50,  // Y position
    100, // HP
    25,  // DMG
    15,   // Atk Spd
    1,   // Spd
    3,   // Range
    0,
    0,
    0};

Enemy Goblin = {
    6,   // Tile ID
    120, // X position
    50,  // Y position
    50,  // HP
    10,  // DMG
    10,   // Atk Spd
    1,   // Spd
    1,   // Range
    0,   // 
    0,
    0};

// End of Test Vars

void init_gfx()
{
    // Load Background tiles and then map
    set_bkg_data(0, 48, Tiles);
    set_bkg_tiles(0, 0, MapWidth, MapHeight, Map);

    SPRITES_8x8;
    set_sprite_data(0, 7, tiles);
    set_sprite_tile(0, 1);
    set_sprite_tile(1, 2);
    move_sprite(0, x, y);
    move_sprite(1, x + 50, y);

    SHOW_SPRITES;

    SHOW_BKG;

    DISPLAY_ON;
}

void init_units(Unit *unit_group)
{
    for (int i = 0; i < NR_PLAYER_UNITS; i++)
    {
        unit_group[i].alive = 0;
    }
}



void unit_scroll_correct(Unit *unit, uint8_t posdir){
    if (posdir) unit->x -= 1;
    else unit->x += 1;
}

void enemy_scroll_correct(Enemy *enemy, uint8_t posdir){
    if (posdir) enemy->x -= 1;
    else enemy->x += 1;
}



void main(void)
{
    init_gfx();
    init_units(player_units);

    spawn_unit(&Soldier, player_units);

    spawn_enemy(&Goblin, enemy_units);

    // Loop forever
    while (1)
    {
        // printf("%d\n", sys_time);

        // for (int i = 0; i < NR_PLAYER_UNITS; i++)
        // {
        //     printf("%d: %d\n", i, player_units[i].x);
        // }

        prev_input = curr_input;
        curr_input = joypad();

        if (curr_input & J_A){
            scroll_bkg(1, 0);
            for (int i = 0; i < NR_PLAYER_UNITS; i++) {
                if (player_units[i].alive){
                    unit_scroll_correct(&player_units[i], 1);
                }

                if (enemy_units[i].alive){
                    enemy_scroll_correct(&enemy_units[i], 1);
                }
            }
        }

        if (curr_input & J_B){
            scroll_bkg(-1, 0);
            for (int i = 0; i < NR_PLAYER_UNITS; i++) {
                if (player_units[i].alive){
                    unit_scroll_correct(&player_units[i], 0);
                }

                if (enemy_units[i].alive){
                    enemy_scroll_correct(&enemy_units[i], 0);
                }
            }
        }

        // if ((curr_input & J_A) && !(prev_input & J_A))
        // {
        //     spawn_unit(&Soldier, player_units);
        //     delay(100);
        // }

        // if ((curr_input & J_B) && !(prev_input & J_B))
        // {
        //     spawn_unit(&Archer, player_units);
        //     delay(100);
        // }

        for (int i = 0; i < NR_PLAYER_UNITS; i++)
        {
            if (player_units[i].alive == 1)
            {
                uint8_t closestID;
                if ((get_closest_enemy(&player_units[i], enemy_units, &closestID)) < player_units[i].range * RANGE_UNIT)
                {
                    atk_enemy(&player_units[i], &enemy_units[closestID]);
                    // printf("%d\n", enemy_units[closestID].hp);
                }
                else
                {
                    move_unit(&player_units[i]);
                }

                if (player_units[i].hp <= 0) player_units[i].alive = 0;
                // printf("%d: %d\n", i, player_units[i].alive);
            }
        }

        for (int i = 0; i < NR_ENEMY_UNITS; i++)
        {
            if (enemy_units[i].alive == 1)
            {
                if ((get_closest_unit(&enemy_units[i], player_units)) < enemy_units[i].range * RANGE_UNIT)
                {
                    // Attack?
                }
                else
                {
                    move_enemy(&enemy_units[i]);
                }

                if (enemy_units[i].hp <= 0)
                {
                    // printf("HERE!\n");
                    kill_enemy(&enemy_units[i]);
                }
            }
        }

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
