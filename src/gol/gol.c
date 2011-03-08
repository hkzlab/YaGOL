#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "gol/gol.h"

static Uint8* main_gol_grid;
static Uint8* back_gol_grid;

static Uint16 gol_grid_width;
static Uint16 gol_grid_height;

// Counter, increments at every step
static Uint32 gol_step_counter;

// Kind of rule to use for GoL steps
static Uint8 gol_current_rule;

#define GRID_POINT(grid, x, y) (*(grid + x + (y * gol_grid_width)))

// Standard GoL rules
#define STD_UNDER 2
#define STD_OVER 3
#define STD_REPR 3
#define STD_REPR_M 3
#define STD_REPRCH 100

#define MAX_GOL_RULES 1

// { UNDERPOPULATION, OVERPOPULATION, REPRODUCTION}
static Uint8 gol_rules[MAX_GOL_RULES][5] = {{STD_UNDER, STD_OVER, STD_REPR, STD_REPR_M, STD_REPRCH}};

#define REPRCH_RULE (gol_rules[gol_current_rule][4])
#define REP_M_RULE (gol_rules[gol_current_rule][3])
#define REP_RULE (gol_rules[gol_current_rule][2])
#define OVER_RULE (gol_rules[gol_current_rule][1])
#define UNDER_RULE (gol_rules[gol_current_rule][0])

void flip_gol_grids(void);

void init_gol(Uint16 grid_width, Uint16 grid_height) {
	gol_grid_width = grid_width;
	gol_grid_height = grid_height;

	gol_step_counter = 0;
	gol_current_rule = 0;

	// Allocate the grids
	main_gol_grid = (Uint8*)malloc(grid_width * grid_height);
	back_gol_grid = (Uint8*)malloc(grid_width * grid_height);

	// Empty the grids
	memset(main_gol_grid, 0, grid_width * grid_height);
	memset(back_gol_grid, 0, grid_width * grid_height);
}

void deinit_gol(void) {
	free(main_gol_grid);
	free(back_gol_grid);
}

void randomize_gol(void) {
	Uint16 x, y;

	for (x = 0; x < gol_grid_width; x++)
		for (y = 0; y < gol_grid_height; y++) {
			GRID_POINT(main_gol_grid, x, y) = random() % 2;
		}
}

void reset_gol(void) {
	gol_step_counter = 0;

	// Empty the grids
	memset(main_gol_grid, 0, gol_grid_width * gol_grid_height);
	memset(back_gol_grid, 0, gol_grid_width * gol_grid_height);	
}

Uint8 get_gol_node(Uint16 x, Uint16 y) {
	return GRID_POINT(main_gol_grid, x, y);
}

void set_gol_node(Uint8 val, Uint16 x, Uint16 y) {
	GRID_POINT(main_gol_grid, x, y) = val;
}

Uint32 gol_step(void) {
	Uint16 x, y;

	// Count a step.	
	gol_step_counter++;

	for (x = 0; x < gol_grid_width; x++)
		for (y = 0; y < gol_grid_height; y++) {
			// MAIN one
			; // x, y are the coord values	

			// TOP one
			Uint16 top_x, top_y;
			top_x = x;
			top_y = (y == 0) ? (gol_grid_height - 1) : (y - 1);

			// BOTTOM one
			Uint16 bottom_x, bottom_y;
			bottom_x = x;
			bottom_y = (y == (gol_grid_height - 1)) ? 0 : (y + 1);

			// LEFT one
			Uint16 left_x, left_y;
			left_x = (y == 0) ? (gol_grid_width - 1) : (x - 1);
			left_y = y;

			// RIGHT one
			Uint16 right_x, right_y;
			right_x = (y == (gol_grid_width - 1)) ? 0 : (x + 1);
			right_y = y;

			// Now we have the coords for all the neighbours
			Uint8 main_val = GRID_POINT(main_gol_grid, x, y) > 0;
			Uint8 top_val = GRID_POINT(main_gol_grid, top_x, top_y) > 0;
			Uint8 bottom_val = GRID_POINT(main_gol_grid, bottom_x, bottom_y) > 0;
			Uint8 left_val = GRID_POINT(main_gol_grid, left_x, left_y) > 0;
			Uint8 right_val = GRID_POINT(main_gol_grid, right_x, right_y) > 0;

			Uint8 total_neighbours = top_val + bottom_val + left_val + right_val;

			if (!main_val && ((total_neighbours >= REP_RULE) && (total_neighbours <= REP_M_RULE)))
				if ((rand() % 100) < (REPRCH_RULE + 5 * (total_neighbours - REP_RULE))) GRID_POINT(back_gol_grid, x, y) = 1; // Cell borns
				else GRID_POINT(back_gol_grid, x, y) = 0; // Cell is stillborn!
			else if (main_val && (total_neighbours < UNDER_RULE || total_neighbours > OVER_RULE))
				GRID_POINT(back_gol_grid, x, y) = 0; // Cell dies
			else if (main_val)
				GRID_POINT(back_gol_grid, x, y) = 1; // Cell remains alive
			else
				GRID_POINT(back_gol_grid, x, y) = 0; // Cell remains dead
		}

	flip_gol_grids();

	return gol_step_counter;
}

Uint32 gol_multiple_steps(Uint8 steps) {
	while (steps--)
		gol_step();

	return gol_step_counter;
}

Uint16 get_gol_grid_width(void) {
	return gol_grid_width;
}

Uint16 get_gol_grid_height(void) {
	return gol_grid_height;
}

Uint8 get_gol_current_rule(void) {
	return gol_current_rule;
}

void set_gol_current_rule(Uint8 rule) {
	gol_current_rule = rule;
}

void flip_gol_grids(void) {
	Uint8 *temp_grid = back_gol_grid;

	back_gol_grid = main_gol_grid;
	main_gol_grid = temp_grid;
}

