#ifndef CGOL_WORLD_H_
#define CGOL_WORLD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct _cgol_world_t cgol_world_t;

enum cgol_state {
  STATE_POPULATED,
  STATE_UNPOPULATED
};


cgol_world_t *
  cgol_world_new(size_t width, size_t height);

void
  cgol_world_destroy(cgol_world_t **world);

void
  cgol_world_set_cell(
    cgol_world_t *world,
    size_t x, size_t y,
    enum cgol_state state
  );

int
  cgol_world_step_simulation(cgol_world_t *world);

void
  cgol_world_print(cgol_world_t *world);

enum cgol_state
  cgol_world_cell(cgol_world_t *world, size_t x, size_t y);


#ifdef __cplusplus
}
#endif

#endif
