#include <gb/gb.h>

#include <stdint.h>
#include <stdio.h>

#include "../res/dungeon_map.h"
#include "../res/dungeon_tiles.h"
#include "../res/test.h"
#include "units.h"

// Global Vars
Unit player_units[NR_PLAYER_UNITS] = {{0}};

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
    1,   // Atk Spd
    1,   // Spd
    1,   // Range
    0,
    1    
};

Unit Archer = {
    2,   // Tile ID
    70,  // X position
    50,  // Y position
    100, // HP
    25,  // DMG
    1,   // Atk Spd
    1,   // Spd
    1,   // Range
    0,
    0
};
// End of Test Vars

void init_gfx()
{
    // Load Background tiles and then map
    // set_bkg_data(0, 79u, dungeon_tiles);
    // set_bkg_tiles(0, 0, 32u, 32u, dungeon_mapPLN0);

    // Turn the background map on to make it visible
    // SHOW_BKG;

    SPRITES_8x8;
    set_sprite_data(0, 5, tiles);
    set_sprite_tile(0, 1);
    set_sprite_tile(1, 2);
    move_sprite(0, x, y);
    move_sprite(1, x + 50, y);

    SHOW_SPRITES;
}

void init_units(Unit *unit_group){
    for (int i = 0; i < NR_PLAYER_UNITS; i++){
        unit_group[i].alive = 0;
    }
}

void main(void)
{
    init_gfx();
    init_units(player_units);

    spawn_unit(&Soldier, player_units);

    for (int i = 0; i < NR_PLAYER_UNITS; i++){
        printf("%d: %d\n", i, player_units[i].alive);
    }

    // Joypad input

    // Loop forever
    while (1)
    {
        //printf("%d\n", sys_time);

        prev_input = curr_input;
        curr_input = joypad();

        if ((curr_input & J_A) && !(prev_input & J_A))
        {
            spawn_unit(&Soldier, player_units);
            delay(100);
        }

        if ((curr_input & J_B) && !(prev_input & J_B))
        {
            spawn_unit(&Archer, player_units);
            delay(100);
        }


        for (int i = 0; i < NR_PLAYER_UNITS; i++){
            if (player_units[i].alive == 1) {
                move_unit(&player_units[i]);
                // printf("%d: %d\n", i, player_units[i].alive);
            }
        }

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}