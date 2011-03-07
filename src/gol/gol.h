#ifndef _GOL_HEADER_
#define _GOL_HEADER_

#include "common/defs.h"

// Initialize GoL and instantiate memory
void init_gol(uint16 grid_width, uint16 grid_height);

// De-Initialize GoL and free memory
void deinit_gol(void);
 
// Regardless of current status, randomize grid
void randomize_gol(void);

// Reset GoL counters and blank the grid
void reset_gol(void);

// Get GoL node status in the grid
uint8 get_gol_node(uint16 x, uint16 y);

// Set GoL node status in the grid
void set_gol_node(uint8 val, uint16 x, uint16 y);

// Get GoL grid sizes
uint16 get_gol_grid_width(void);
uint16 get_gol_grid_height(void);

// getter and setter for current GoL rules
uint8 get_gol_current_rule(void);
void set_gol_current_rule(uint8 rule);

// Perform a GoL step and return current (after-step) counter
uint32 gol_step(void);

// Perform 'steps' steps of GoL and return after-exec step number
uint32 gol_multiple_steps(uint8 steps);

#endif /* _GOL_HEADER_ */
