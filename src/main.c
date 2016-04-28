#include <stdio.h>
#include <unistd.h>


/**
 *
 * conway's game of life
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
  cgol_world_t *world = cgol_world_new(10, 10);

  cgol_world_set_cell(world, 2, 2, STATE_POPULATED);
  cgol_world_set_cell(world, 2, 3, STATE_POPULATED);
  cgol_world_set_cell(world, 2, 4, STATE_POPULATED);

  cgol_world_set_cell(world, 4, 5, STATE_POPULATED);
  cgol_world_set_cell(world, 5, 5, STATE_POPULATED);
  cgol_world_set_cell(world, 6, 5, STATE_POPULATED);
  cgol_world_set_cell(world, 6, 4, STATE_POPULATED);
  cgol_world_set_cell(world, 5, 3, STATE_POPULATED);
  cgol_world_print(world);

  int x;

  while(cgol_world_step_simulation(world)) {
    printf("\n");
    cgol_world_print(world);
    //sleep(1);
  }

  cgol_world_destroy(&world);
}
