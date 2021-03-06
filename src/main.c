#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "common/defs.h"
#include "events/events.h"
#include "gol/gol.h"
#include "drawing/drawing.h"
#include "text/text.h"


extern SDL_Surface *sdl_screen;
extern Uint8 should_quit, should_redraw_grid, fast_forward, paused;
extern Uint16 cell_grid_x, cell_grid_y, cell_grid_size;

int main(void) {

	// Init system
	if (!init_system()) {
		fprintf(stderr, "Error initializing system. Exiting.\n");

		deinit_system();
		exit(-1);
	}

	SDL_Rect clear_text_rect;

	clear_text_rect.x = 30;
	clear_text_rect.y = GRAPH_HEIGHT - 30;
	clear_text_rect.w = GRAPH_WIDTH - clear_text_rect.x;
	clear_text_rect.h = GRAPH_HEIGHT - clear_text_rect.y;

	char step_string[80];

	// seed random number generator
	srand(time(NULL));

	// Initialize Game of Life engine
	init_gol(DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);

	// Draw the main GUI 
	dw_gui_drawControlDeck(sdl_screen, HCenter, VTop);
	
	cell_grid_size = DEFAULT_CELL_SIZE;
	cell_grid_x = (GRAPH_WIDTH - (DEFAULT_GRID_WIDTH * cell_grid_size)) / 2;
	cell_grid_y = 53;
	dw_drawBox(sdl_screen, SDL_MapRGB(sdl_screen->format, 150, 150, 150), cell_grid_x - 3, cell_grid_y - 3, (DEFAULT_GRID_WIDTH * cell_grid_size) + 6, (DEFAULT_GRID_HEIGHT * cell_grid_size) + 6, 3);
	dw_gol_drawGoLPlane(sdl_screen, cell_grid_x, cell_grid_y, DEFAULT_CELL_SIZE, SDL_MapRGB(sdl_screen->format, 0, 200, 0), SDL_MapRGB(sdl_screen->format, 0, 100, 0));

	snprintf(step_string, 79, "Step: %.8u", get_gol_step());
	print_text_simple(sdl_screen, step_string, clear_text_rect.x, clear_text_rect.y);
	
	SDL_Flip(sdl_screen);

	// Main program loop.
	while (!should_quit) {
		// Poll and handle events
		poll_sdl_events();

		if (!paused) {
			if (!fast_forward)
				gol_step();
			else
				gol_multiple_steps(8);

			should_redraw_grid = 1;
		}

		if (should_redraw_grid) {
			dw_gol_drawGoLPlane(sdl_screen, cell_grid_x, cell_grid_y, DEFAULT_CELL_SIZE, SDL_MapRGB(sdl_screen->format, 0, 200, 0), SDL_MapRGB(sdl_screen->format, 0, 100, 0));
			
			SDL_FillRect(sdl_screen, &clear_text_rect, SDL_MapRGB(sdl_screen->format, 0, 0, 0)); // Clear text spacen
			
			snprintf(step_string, 79, "Step: %.8u", get_gol_step());
			print_text_simple(sdl_screen, step_string, clear_text_rect.x, clear_text_rect.y);

			SDL_Flip(sdl_screen);
		
			should_redraw_grid = 0;
		}

		SDL_Delay(100);
	}

	deinit_system();
	return 0;
}

int init_system(void) {
	should_quit = 0;
	should_redraw_grid = 0;
	fast_forward = 0;
	paused = 1;

	// Init... everything.
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
     	fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return 0;
	}

 	if (!(sdl_screen = SDL_SetVideoMode(GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF))) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	// Set window title
	SDL_WM_SetCaption("YaGOL! Yet another Game Of Life...", NULL);

	// Init text subsys
	init_text();

	return 1;
}

void deinit_system(void) {
	// Deinit GoL engine
	deinit_gol();

	// Deinit text subsystem
	deinit_text();

	// Free screen surface
	SDL_FreeSurface(sdl_screen);

	// de-init SDL
	SDL_Quit();

}

