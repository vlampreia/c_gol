#include "grid.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


struct _cgol_grid_t {
  size_t rows;
  size_t columns;

  size_t element_size;

  void **values;
};


cgol_grid_t *cgol_grid_new(size_t rows, size_t cols, size_t element_size) {
  cgol_grid_t *grid = malloc(sizeof(cgol_grid_t));
  assert(grid);

  grid->rows = rows;
  grid->columns = cols;
  grid->element_size = element_size;

  grid->values = malloc(rows*cols*element_size*sizeof (void*));

  for (size_t i = 0; i < rows*cols; ++i) {
    grid->values[i] = NULL;
  }

  return grid;
}


void cgol_grid_destroy(cgol_grid_t **grid) {
  assert(grid);

  cgol_grid_t *self = *grid;

  for (size_t i = 0; i < self->rows * self->columns; ++i) {
    free(self->values[i]);
  }

  free(self->values);
  free(self);

  *grid = NULL;
}


cgol_grid_t *cgol_grid_copy(cgol_grid_t *grid) {
  assert(grid);

  cgol_grid_t *copy = malloc(sizeof(cgol_grid_t));
  assert(copy);

  copy->rows         = grid->rows;
  copy->columns      = grid->columns;
  copy->element_size = grid->element_size;

  size_t values_size = copy->rows * copy->columns *
                       copy->element_size * sizeof (void*);

  copy->values = malloc(values_size);
  assert(copy->values);

  for (size_t i = 0; i < copy->rows * copy->columns; ++i) {
    copy->values[i] = malloc(copy->element_size);
    memcpy(copy->values[i], grid->values[i], copy->element_size);
  }

  return copy;
}


void cgol_grid_set(cgol_grid_t *grid, size_t row, size_t col, void *value) {
  assert(grid);

  void **element = &grid->values[row * grid->columns + col];
  if(!*element) *element = malloc(grid->element_size);
  assert(*element);
  memcpy(*element, value, grid->element_size);
}


void *cgol_grid_at(cgol_grid_t *grid, size_t row, size_t col) {
  assert(grid);
  assert(row < grid->rows);
  assert(col < grid->columns);

  return grid->values[row * grid->columns + col];
}
