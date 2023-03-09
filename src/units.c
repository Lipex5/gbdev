#include "units.h"

int cooldown = SPAWN_COOLDOWN * 60; // Secs
int next_use = 0;

// ========= Unit functions

void spawn_unit(Unit *unit, Unit *unit_group)
{
    if (sys_time > next_use)
    {
        // printf("%d\n", next_use);
        for (int j = 0; j < NR_PLAYER_UNITS; j++)
        {
            if (unit_group[j].alive == 0)
            {
                for (int i = 0; i < MAX_SPRITES; i++)
                {
                    if (get_sprite_tile(i) == 0)
                    {
                        set_sprite_tile(i, unit->tileID);
                        move_sprite(i, unit->x, unit->y);
                        unit_group[j] = *unit;
                        unit_group[j].spriteID = i;
                        unit_group[j].alive = 1;
                        next_use = sys_time + cooldown;
                        // printf("Spawned Unit\n");
                        return;
                    }
                }
            }
        }
    }
}

void move_unit(Unit *unit)
{
    if (unit->frame_counter == 0)
    {
        unit->x += 1;
        // move_sprite(unit->spriteID, unit->x, unit->y);
        scroll_sprite(unit->spriteID, 1, 0);
        unit->frame_counter = MAX_SPEED - unit->speed;
    }
    else
        unit->frame_counter--;
}

uint8_t get_closest_enemy(Unit *unit, Enemy *unit_group, uint8_t *returnID){
    uint8_t closest = 254;
    for (int i = 0; i < 1; i++){
        if (unit_group[i].alive && abs(unit_group[i].x - unit->x) < closest) {
            closest = abs(unit_group[i].x - unit->x);
            *returnID = i;
        }
    }
    return closest;
}

void atk_enemy(Unit *unit, Enemy *enemy){
    if (sys_time > unit->atkspd_counter)
    {
        enemy->hp -= unit->dmg;
        unit->atkspd_counter = sys_time + (ATKSPD_MULT * unit->atkspd);
    }
}

void kill_unit (Unit *unit){
    unit->spriteID = 0;
    unit->alive = 0;
}


// ============= Enemy Functions

void spawn_enemy(Enemy *unit, Enemy *unit_group)
{
    // printf("%d\n", next_use);
    for (int j = 0; j < NR_ENEMY_UNITS; j++)
    {
        if (unit_group[j].alive == 0)
        {
            for (int i = 0; i < MAX_SPRITES; i++)
            {
                if (get_sprite_tile(i) == 0)
                {
                    set_sprite_tile(i, unit->tileID);
                    move_sprite(i, unit->x, unit->y);
                    unit_group[j] = *unit;
                    unit_group[j].spriteID = i;
                    unit_group[j].alive = 1;
                    // printf("Spawned Enemy\n");
                    return;
                }
            }
        }
    }
}

void move_enemy(Enemy *unit)
{
    if (unit->frame_counter == 0)
    {
        unit->x -= 1;
        move_sprite(unit->spriteID, unit->x, unit->y);
        unit->frame_counter = MAX_SPEED - unit->speed;
    }
    else
        unit->frame_counter--;
}

uint8_t get_closest_unit(Enemy *unit, Unit *unit_group){
    uint8_t closest = 254;
    for (int i = 0; i < 1; i++){
        if (abs(unit_group[i].x - unit->x) < closest) closest = abs(unit_group[i].x - unit->x);
    }
    return closest;
}

void kill_enemy (Enemy *enemy){
    set_sprite_tile(enemy->spriteID, 0);
    hide_sprite(enemy->spriteID);
    enemy->spriteID = 0;
    enemy->alive = 0;
}