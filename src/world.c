#include "world.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "grid.h"


struct _cgol_world_t {
  size_t width;
  size_t height;

  cgol_grid_t *cell_grid;
};


cgol_world_t *cgol_world_new(size_t width, size_t height) {
  cgol_world_t *world = malloc(sizeof(cgol_world_t));
  assert(world);

  world->width = width;
  world->height = height;
  world->cell_grid = cgol_grid_new(height, width, sizeof(enum cgol_state));

  enum cgol_state default_state = STATE_UNPOPULATED;

  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      cgol_grid_set(world->cell_grid, row, col, &default_state);
    }
  }

  return world;
}


void cgol_world_destroy(cgol_world_t **world) {
  assert(world);

  cgol_world_t *self = *world;

  cgol_grid_destroy(&self->cell_grid);
  free(self);

  *world = NULL;
}


void cgol_world_set_cell(
  cgol_world_t *world,
  size_t x, size_t y,
  enum cgol_state state
) {
  assert(world);

  cgol_grid_set(world->cell_grid, y, x, &state);
}

static int cgol_world_neighbours(cgol_world_t *world, size_t x, size_t y) {
  int count = 0;
  size_t top   = y > 0? y-1: y;
  size_t bot   = y < world->height-1? y+1: y;
  size_t left  = x > 0? x-1: x;
  size_t right = x < world->width-1? x+1: x;

  for (size_t _y = top; _y <= bot; ++_y) {
    for (size_t _x = left; _x <= right; ++_x) {
      if (_x == x && _y == y) continue;
      if (*(enum cgol_state*) cgol_grid_at(world->cell_grid, _y, _x) == STATE_POPULATED) ++count;
    }
  }

  return count;
}


int cgol_world_step_simulation(cgol_world_t *world) {
  assert(world);

  cgol_grid_t *new_state = cgol_grid_copy(world->cell_grid);

  int changes = 0;

  for (size_t y = 0; y < world->height; ++y) {
    for (size_t x = 0; x < world->width; ++x) {
      int modified = 0;
      int neighbours = cgol_world_neighbours(world, x, y);

      enum cgol_state cell_state = STATE_UNPOPULATED;

      if (cgol_world_cell(world, x, y) == STATE_POPULATED) {
        if (neighbours < 2) {
          cell_state = STATE_UNPOPULATED;
          modified = 1;
        } else if (neighbours > 3) {
          cell_state = STATE_UNPOPULATED;
          modified = 1;
        }
      } else {
        if (neighbours == 3) {
          cell_state = STATE_POPULATED;
          modified = 1;
        }
      }

      if (modified) {
        cgol_grid_set(new_state, y, x, &cell_state);
        changes = 1;
      }
    }
  }

  cgol_grid_destroy(&world->cell_grid);
  world->cell_grid = new_state;

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

  return *(enum cgol_state*) cgol_grid_at(world->cell_grid, y, x);
}
