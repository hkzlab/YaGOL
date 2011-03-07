#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <time.h>

#include "main.h"
#include "common/defs.h"
#include "events/events.h"
#include "gol/gol.h"


extern SDL_Surface *sdl_screen;

int main(void) {

	// Init system
	if (!init_system()) {
		fprintf(stderr, "Error initializing system. Exiting.\n");

		deinit_system();
		exit(-1);
	}

	// seed random number generator
	srand(time(NULL));

	// Main program loop.
	while (1) {
		// Poll and handle events
		poll_sdl_events();

		usleep(100000);
	}

	// We should NEVER get here
	deinit_system();
	return 0;
}

int init_system(void) {
	// Init... everything.
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
     	fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return 0;
	}

 	if (!(sdl_screen = SDL_SetVideoMode(GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF))) {
		fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
		return 0;
	}

	return 1;
}

void deinit_system(void) {
	SDL_FreeSurface(sdl_screen);

	// de-init SDL
	SDL_Quit();

}

