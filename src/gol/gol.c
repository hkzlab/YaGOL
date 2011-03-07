#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "gol/gol.h"

static uint8* main_gol_grid;
static uint8* back_gol_grid;

static uint16 gol_grid_width;
static uint16 gol_grid_height;

// Counter, increments at every step
static uint32 gol_step_counter;

// Kind of rule to use for GoL steps
static uint8 gol_current_rule;

#define GRID_POINT(grid, x, y) (*(grid + x + (y * gol_grid_width)))

// Standard GoL rules
#define STD_UNDER 2
#define STD_OVER 3
#define STD_REPR 3
#define STD_REPR_M 3
#define STD_REPRCH 100

#define MAX_GOL_RULES 1

// { UNDERPOPULATION, OVERPOPULATION, REPRODUCTION}
static uint8 gol_rules[MAX_GOL_RULES][5] = {{STD_UNDER, STD_OVER, STD_REPR, STD_REPR_M, STD_REPRCH}};

#define REPRCH_RULE (gol_rules[gol_current_rule][4])
#define REP_M_RULE (gol_rules[gol_current_rule][3])
#define REP_RULE (gol_rules[gol_current_rule][2])
#define OVER_RULE (gol_rules[gol_current_rule][1])
#define UNDER_RULE (gol_rules[gol_current_rule][0])

void flip_gol_grids(void);

void init_gol(uint16 grid_width, uint16 grid_height) {
	gol_grid_width = grid_width;
	gol_grid_height = grid_height;

	gol_step_counter = 0;
	gol_current_rule = 0;

	// Allocate the grids
	main_gol_grid = (uint8*)malloc(grid_width * grid_height);
	back_gol_grid = (uint8*)malloc(grid_width * grid_height);

	// Empty the grids
	memset(main_gol_grid, 0, grid_width * grid_height);
	memset(back_gol_grid, 0, grid_width * grid_height);
}

void deinit_gol(void) {
	free(main_gol_grid);
	free(back_gol_grid);
}

void randomize_gol(void) {
	uint16 x, y;

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

uint8 get_gol_node(uint16 x, uint16 y) {
	return GRID_POINT(main_gol_grid, x, y);
}

void set_gol_node(uint8 val, uint16 x, uint16 y) {
	GRID_POINT(main_gol_grid, x, y) = val;
}

uint32 gol_step(void) {
	uint16 x, y;

	// Count a step.	
	gol_step_counter++;

	for (x = 0; x < gol_grid_width; x++)
		for (y = 0; y < gol_grid_height; y++) {
			// MAIN one
			; // x, y are the coord values	

			// TOP one
			uint16 top_x, top_y;
			top_x = x;
			top_y = (y == 0) ? (gol_grid_height - 1) : (y - 1);

			// BOTTOM one
			uint16 bottom_x, bottom_y;
			bottom_x = x;
			bottom_y = (y == (gol_grid_height - 1)) ? 0 : (y + 1);

			// LEFT one
			uint16 left_x, left_y;
			left_x = (y == 0) ? (gol_grid_width - 1) : (x - 1);
			left_y = y;

			// RIGHT one
			uint16 right_x, right_y;
			right_x = (y == (gol_grid_width - 1)) ? 0 : (x + 1);
			right_y = y;

			// Now we have the coords for all the neighbours
			uint8 main_val = GRID_POINT(main_gol_grid, x, y) > 0;
			uint8 top_val = GRID_POINT(main_gol_grid, top_x, top_y) > 0;
			uint8 bottom_val = GRID_POINT(main_gol_grid, bottom_x, bottom_y) > 0;
			uint8 left_val = GRID_POINT(main_gol_grid, left_x, left_y) > 0;
			uint8 right_val = GRID_POINT(main_gol_grid, right_x, right_y) > 0;

			uint8 total_neighbours = top_val + bottom_val + left_val + right_val;

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

uint32 gol_multiple_steps(uint8 steps) {
	while (steps--)
		gol_step();

	return gol_step_counter;
}

uint16 get_gol_grid_width(void) {
	return gol_grid_width;
}

uint16 get_gol_grid_height(void) {
	return gol_grid_height;
}

uint8 get_gol_current_rule(void) {
	return gol_current_rule;
}

void set_gol_current_rule(uint8 rule) {
	gol_current_rule = rule;
}

void flip_gol_grids(void) {
	uint8 *temp_grid = back_gol_grid;

	back_gol_grid = main_gol_grid;
	main_gol_grid = temp_grid;
}

