#include "units.h"

int cooldown = SPAWN_COOLDOWN * 60; // Secs
int next_use = 0;

void spawn_unit(Unit *unit, Unit *unit_group)
{
    if (sys_time > next_use)
    {
        //printf("%d\n", next_use);
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
                        printf("Spawned Unit\n");
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
        move_sprite(unit->spriteID, unit->x, unit->y);
        unit->frame_counter = MAX_SPEED - unit->speed;
    }
    else
        unit->frame_counter--;
}