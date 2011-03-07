#include "events/events.h"

#include <SDL/SDL.h>

void poll_sdl_events(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_QUIT:
				deinit_system();
				exit(0);
		}
	}
}

