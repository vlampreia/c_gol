#include "world.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>



struct _cgol_world_t {
  size_t width;
  size_t height;

  enum cgol_state *cell_grid;
};


cgol_world_t *cgol_world_new(size_t width, size_t height) {
  cgol_world_t *world = malloc(sizeof(cgol_world_t));
  assert(world);

  world->width = width;
  world->height = height;
  world->cell_grid = malloc(width*height*sizeof(enum cgol_state));
  assert(world->cell_grid);

  for (size_t i = 0; i < width*height; ++i) {
    world->cell_grid[i] = STATE_UNPOPULATED;
  }

  return world;
}


void cgol_world_destroy(cgol_world_t **world) {
  assert(world);

  cgol_world_t *self = *world;

  free(self->cell_grid);
  free(self);

  *world = NULL;
}


static void s_grid_set(enum cgol_state *grid, size_t x, size_t width, size_t y, enum cgol_state state) {
  grid[width * y + x] = state;
}


void cgol_world_set_cell(
  cgol_world_t *world,
  size_t x, size_t y,
  enum cgol_state state
) {
  assert(world);

  s_grid_set(world->cell_grid, x, world->width, y, state);
}

static int cgol_world_neighbours(cgol_world_t *world, size_t x, size_t y) {
  int count = 0;
  size_t top = y > 0? y-1: y;
  size_t bot = y < world->height-1? y+1: y;
  size_t left = x > 0? x-1: x;
  size_t right = x < world->width-1? x+1: x;
  //size_t top = y-1;
  //size_t bot = y+1;
  //size_t left = x-1;
  //size_t right = x+1;

  for (size_t _y = top; _y <= bot; ++_y) {
    for (size_t _x = left; _x <= right; ++_x) {
      if(_x == x && _y == y) continue;
      if (cgol_world_cell(world, _x, _y) == STATE_POPULATED) ++count;
    }
  }

  return count;
}


int cgol_world_step_simulation(cgol_world_t *world) {
  assert(world);

  enum cgol_state *newState = malloc(world->width*world->height*sizeof(enum cgol_state));
  assert(newState);

  memcpy(newState, world->cell_grid, world->width*world->height*sizeof(enum cgol_state));

  int changes = 0;

  for (size_t y = 0; y < world->height; ++y) {
    for (size_t x = 0; x < world->width; ++x) {
      int neighbours = cgol_world_neighbours(world, x, y);

      if (cgol_world_cell(world, x, y) == STATE_POPULATED) {
        if (neighbours < 2) {
          s_grid_set(newState, x, world->width, y, STATE_UNPOPULATED);
          changes = 1;
        } else if (neighbours > 3) {
          s_grid_set(newState, x, world->width, y, STATE_UNPOPULATED);
          changes = 1;
        }
      } else {
        if (neighbours == 3) {
          s_grid_set(newState, x, world->width, y, STATE_POPULATED);
          changes = 1;
        }
      }
    }
  }

  free(world->cell_grid);
  world->cell_grid = newState;

  return changes;
}


void cgol_world_print(cgol_world_t *world) {
  assert(world);

  for (size_t y = 0; y < world->height; ++y) {
    for (size_t x = 0; x < world->width; ++x) {
      if (cgol_world_cell(world, x, y) == STATE_POPULATED) {
        printf("[%d]", cgol_world_neighbours(world, x, y));
      } else {
        printf(" %d ", cgol_world_neighbours(world, x, y));
      }
    }
    printf("\n");
  }
}


enum cgol_state cgol_world_cell(cgol_world_t *world, size_t x, size_t y) {
  assert(world);

  return world->cell_grid[world->width * y + x];
}
