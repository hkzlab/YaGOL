#include "events/events.h"
#include "common/defs.h"

extern Uint8 should_quit, should_redraw_grid, fast_forward, paused;
extern Uint16 all_button_y, chaos_button_x, fastf_button_x, quit_button_x, start_button_x, step_button_x, stop_button_x;

void button_press(SDL_MouseButtonEvent *ev);

void poll_sdl_events(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				button_press(&(event.button));
				break;
			case SDL_QUIT:
				should_quit = 1;
				break;
		}
	}
}

void button_press(SDL_MouseButtonEvent *ev) {
	assert(ev);

	if (ev->button != SDL_BUTTON_LEFT) return;
	
	if(ev->y >= all_button_y && ev->y <= all_button_y + BUTTON_WIDTH) { // The click might be on a button
		if (ev->x >= quit_button_x && ev->x <= quit_button_x + BUTTON_WIDTH) // QUIT button
			should_quit = 1;
		else if (ev->x >= chaos_button_x && ev->x <= chaos_button_x + BUTTON_WIDTH) { // CHAOS button
			randomize_gol();
			should_redraw_grid = 1;
		} else if (ev->x >= fastf_button_x && ev->x <= fastf_button_x + BUTTON_WIDTH) { // FASTF button
			fast_forward = !fast_forward;
			paused = 0;
		} else if (ev->x >= start_button_x && ev->x <= start_button_x + BUTTON_WIDTH) { // START button
			paused = 0;
			fast_forward = 0;
		} else if (ev->x >= step_button_x && ev->x <= step_button_x + BUTTON_WIDTH) { // STEP button
			if (!paused) paused = 1;
			else {
				gol_step();
				should_redraw_grid = 1;
			}
		} else if (ev->x >= stop_button_x && ev->x <= stop_button_x + BUTTON_WIDTH) { // STOP button
			paused = 1;
			reset_gol();
			should_redraw_grid = 1;
		}
	}
}
