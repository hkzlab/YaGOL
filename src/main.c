#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "common/defs.h"
#include "events/events.h"
#include "gol/gol.h"
#include "drawing/drawing.h"


extern SDL_Surface *sdl_screen;
extern Uint8 should_quit;

int main(void) {

	// Init system
	if (!init_system()) {
		fprintf(stderr, "Error initializing system. Exiting.\n");

		deinit_system();
		exit(-1);
	}

	// seed random number generator
	srand(time(NULL));

	// Initialize Game of Life engine
	init_gol(DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT);
	randomize_gol(); // Randomize GoL grid status

	// Draw the main GUI 
	Uint32 cell_grid_x, cell_grid_y;
	dw_gui_drawControlDeck(sdl_screen, HCenter, VTop);
	
	cell_grid_x = (GRAPH_WIDTH - (DEFAULT_GRID_WIDTH * DEFAULT_CELL_SIZE)) / 2;
	cell_grid_y = 53;
	dw_drawBox(sdl_screen, SDL_MapRGB(sdl_screen->format, 150, 150, 150), cell_grid_x - 3, cell_grid_y - 3, (DEFAULT_GRID_WIDTH * DEFAULT_CELL_SIZE) + 3, (DEFAULT_GRID_HEIGHT * DEFAULT_CELL_SIZE) + 3, 3);

	SDL_Flip(sdl_screen);

	// Main program loop.
	while (!should_quit) {
		// Poll and handle events
		poll_sdl_events();

		gol_step();

		usleep(100000);
	}

	deinit_system();
	return 0;
}

int init_system(void) {
	should_quit = 0;

	// Init... everything.
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
     	fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return 0;
	}

 	if (!(sdl_screen = SDL_SetVideoMode(GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF))) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	SDL_WM_SetCaption("YaGOL! Yet another Game Of Life...", NULL);

	return 1;
}

void deinit_system(void) {
	// Deinit GoL engine
	deinit_gol();

	// Free screen surface
	SDL_FreeSurface(sdl_screen);

	// de-init SDL
	SDL_Quit();

}

