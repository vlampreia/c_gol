#ifndef CGOL_GRID_H
#define CGOL_GRID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct _cgol_grid_t cgol_grid_t;


cgol_grid_t *
  cgol_grid_new(size_t rows, size_t cols, size_t element_size);

void
  cgol_grid_destroy(cgol_grid_t **grid);

cgol_grid_t *
  cgol_grid_copy(cgol_grid_t *grid);

void
  cgol_grid_set(cgol_grid_t *grid, size_t row, size_t col, void *value);

void *
  cgol_grid_at(cgol_grid_t *grid, size_t row, size_t col);


#ifdef __cplusplus
}
#endif

#endif
