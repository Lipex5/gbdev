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

uint8_t bkg_x = 0;

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
    10,  // Atk Spd
    1,   // Spd
    1,   // Range
    0,
    0,
    0,
    0,
    0};

Unit Archer = {
    2,   // Tile ID
    70,  // X position
    50,  // Y position
    100, // HP
    25,  // DMG
    15,  // Atk Spd
    1,   // Spd
    3,   // Range
    0,
    0,
    0,
    0,
    0};

Enemy Goblin = {
    6,   // Tile ID
    120, // X position
    50,  // Y position
    50,  // HP
    10,  // DMG
    10,  // Atk Spd
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

    SHOW_SPRITES;

    SHOW_BKG;

    DISPLAY_ON;
}

// Functions in tests
void unit_scroll_correct(Unit *unit, uint8_t posdir)
{
    if (posdir)
        unit->newx -= 1;
    else
        unit->newx += 1;
}

void enemy_scroll_correct(Enemy *enemy, uint8_t posdir)
{
    if (posdir)
        enemy->newx -= 1;
    else
        enemy->newx += 1;
}

void unit_global_move(Unit *unit)
{
    scroll_sprite(unit->spriteID, unit->newx, unit->newy);

    unit->x += unit->newx;
    unit->y += unit->newy;
    unit->newx = 0;
    unit->newy = 0;
    }

void enemy_global_move(Enemy *enemy)
{
    scroll_sprite(enemy->spriteID, enemy->newx, enemy->newy);

    enemy->x += enemy->newx;
    enemy->y += enemy->newy;
    enemy->newx = 0;
    enemy->newy = 0;
}

void update_bkg()
{
    if ((joypad() & J_A) && bkg_x < 96)
    {
        scroll_bkg(1, 0);
        bkg_x++;
        for (int i = 0; i < NR_PLAYER_UNITS; i++)
        {
            if (player_units[i].alive)
            {
                unit_scroll_correct(&player_units[i], 1);
            }

            if (enemy_units[i].alive)
            {
                enemy_scroll_correct(&enemy_units[i], 1);
            }
        }
    }
    if ((joypad() & J_B) && bkg_x > 0)
    {
        scroll_bkg(-1, 0);
        bkg_x--;
        for (int i = 0; i < NR_PLAYER_UNITS; i++)
        {
            if (player_units[i].alive)
            {
                unit_scroll_correct(&player_units[i], 0);
            }

            if (enemy_units[i].alive)
            {
                enemy_scroll_correct(&enemy_units[i], 0);
            }
        }
    }
}

// End of FiT

void main(void)
{
    init_gfx();

    spawn_unit(&Soldier, player_units, 40, 96);
    // spawn_unit(&Soldier, player_units, 70, 96);
    // spawn_unit(&Soldier, player_units, 60, 96);

    // spawn_enemy(&Goblin, enemy_units, 120, 96);
    // spawn_enemy(&Goblin, enemy_units, 100, 96);
    // spawn_enemy(&Goblin, enemy_units, 140, 96);
    // spawn_enemy(&Goblin, enemy_units, 132, 96);
    // spawn_enemy(&Goblin, enemy_units, 150, 96);
    // spawn_enemy(&Goblin, enemy_units, 200, 96);
    // spawn_enemy(&Goblin, enemy_units, 210, 96);
    // spawn_enemy(&Goblin, enemy_units, 230, 96);

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

        update_bkg();

        // if (curr_input & J_A)
        // {
        //     scroll_bkg(1, 0);
        //     for (int i = 0; i < NR_PLAYER_UNITS; i++)
        //     {
        //         if (player_units[i].alive)
        //         {
        //             unit_scroll_correct(&player_units[i], 1);
        //         }

        //         if (enemy_units[i].alive)
        //         {
        //             enemy_scroll_correct(&enemy_units[i], 1);
        //         }
        //     }
        // }

        // if (curr_input & J_B)
        // {
        //     scroll_bkg(-1, 0);
        //     for (int i = 0; i < NR_PLAYER_UNITS; i++)
        //     {
        //         if (player_units[i].alive)
        //         {
        //             unit_scroll_correct(&player_units[i], 0);
        //         }

        //         if (enemy_units[i].alive)
        //         {
        //             enemy_scroll_correct(&enemy_units[i], 0);
        //         }
        //     }
        // }

        if ((curr_input & J_START) && !(prev_input & J_START))
        {
            spawn_unit(&Soldier, player_units, 40, 96);
            delay(100);
        }

        if ((curr_input & J_SELECT) && !(prev_input & J_SELECT))
        {
            spawn_unit(&Archer, player_units, 40, 96);
            delay(100);
        }

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
                    move_unit(&player_units[i], 1, 0);
                }

                if (player_units[i].hp <= 0)
                {
                    // printf("%d: %d\n", i, player_units[i].alive);
                    kill_unit(&player_units[i]);
                }
            }
        }

        for (int i = 0; i < NR_ENEMY_UNITS; i++)
        {
            if (enemy_units[i].alive == 1)
            {
                uint8_t closestPID;
                if ((get_closest_unit(&enemy_units[i], player_units, &closestPID)) < enemy_units[i].range * RANGE_UNIT)
                {
                    atk_unit(&enemy_units[i], &player_units[closestPID]);
                }
                else
                {
                    move_enemy(&enemy_units[i], -1, 0);
                }

                if (enemy_units[i].hp <= 0)
                {
                    // printf("HERE!\n");
                    kill_enemy(&enemy_units[i]);
                }
            }
        }

        for (int i = 0; i < NR_PLAYER_UNITS; i++)
        {
            if (player_units[i].alive == 1)
            {
                unit_global_move(&player_units[i]);
            }

            if (enemy_units[i].alive == 1)
            {
                enemy_global_move(&enemy_units[i]);
            }
        }

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
// HELLO
// WORLD
// :)