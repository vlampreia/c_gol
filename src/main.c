#include <stdio.h>


/**
 *
 * conway's game of life
 * goal 1: working basic gol
 *
 * rules:
 *  populated cell:
 *    < 2 neighbours: death
 *    > 3 neighbours: death
 *    2-3 neighbours: live
 *  unpopulated:
 *    3 cells: populated
 *
 */


#include "world.h"


int main(int argc, char **argv) {
  printf("Hello\n");

  cgol_world_t *world = cgol_world_new(10, 10);

  cgol_world_set_cell(world, 4, 5, STATE_POPULATED);
  cgol_world_set_cell(world, 5, 5, STATE_POPULATED);
  cgol_world_set_cell(world, 6, 5, STATE_POPULATED);
  cgol_world_set_cell(world, 6, 4, STATE_POPULATED);
  cgol_world_set_cell(world, 5, 3, STATE_POPULATED);
  cgol_world_print(world);

  cgol_world_step_simulation(world);
  printf("\n");
  cgol_world_print(world);

  cgol_world_step_simulation(world);
  printf("\n");
  cgol_world_print(world);

  cgol_world_destroy(&world);
}
