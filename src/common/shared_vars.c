#include "common/defs.h"

SDL_Surface *sdl_screen;

Uint8 should_quit, should_redraw_grid, fast_forward, paused;

// Save button position here, for event management to access
Uint16 all_button_y; // All the buttons are on a single line
Uint16 chaos_button_x, fastf_button_x, quit_button_x, start_button_x, step_button_x, stop_button_x;

// GoL grid position here
Uint16 cell_grid_x, cell_grid_y, cell_grid_size;

Uint32 current_step;

