#ifndef _GOL_HEADER_
#define _GOL_HEADER_

#include "common/defs.h"

// Initialize GoL and instantiate memory
void init_gol(Uint16 grid_width, Uint16 grid_height);

// De-Initialize GoL and free memory
void deinit_gol(void);
 
// Regardless of current status, randomize grid
void randomize_gol(void);

// Reset GoL counters and blank the grid
void reset_gol(void);

// Get GoL node status in the grid
Uint8 get_gol_node(Uint16 x, Uint16 y);

// Set GoL node status in the grid
void set_gol_node(Uint8 val, Uint16 x, Uint16 y);

// Get GoL grid sizes
Uint16 get_gol_grid_width(void);
Uint16 get_gol_grid_height(void);

// getter and setter for current GoL rules
Uint8 get_gol_current_rule(void);
void set_gol_current_rule(Uint8 rule);

// Perform a GoL step and return current (after-step) counter
Uint32 gol_step(void);

// Perform 'steps' steps of GoL and return after-exec step number
Uint32 gol_multiple_steps(Uint8 steps);

// Turns the board into a negative version of itself
void gol_negative_board(void);

// Get GoL step number
Uint32 get_gol_step(void);

#endif /* _GOL_HEADER_ */
