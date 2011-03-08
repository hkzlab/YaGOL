#include "drawing/drawing.h"
#include <SDL/SDL_image.h>

#define CONTROL_DECK "resources/control_deck.png"
#define DECK_LOGO "resources/deck_logo.png"
#define CHAOS_BUTTON "resources/chaos_button.png"
#define FASTF_BUTTON "resources/fastf_button.png"
#define QUIT_BUTTON "resources/quit_button.png"
#define START_BUTTON "resources/start_button.png"
#define STEP_BUTTON "resources/step_button.png"
#define STOP_BUTTON "resources/stop_button.png"

void dw_gui_drawControlDeck(SDL_Surface *s, enum HPosition hpos, enum VPosition vpos) {
	assert(s);

	Uint16 x_deck_pos, y_deck_pos;
	SDL_Surface *main_deck = IMG_Load(CONTROL_DECK);

	if (!main_deck) {
		fprintf(stderr, "dw_gui_drawControlDeck() failed: unable to load image\n");
		return;
	}

	if (SDL_MUSTLOCK(main_deck)) SDL_LockSurface(main_deck);
	assert(main_deck->w <= s->w && main_deck->h <= s->h);

	if (SDL_MUSTLOCK(main_deck)) SDL_UnlockSurface(main_deck);

}
