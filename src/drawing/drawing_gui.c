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

	SDL_Rect src_rect, dst_rect;

	if (!main_deck) {
		fprintf(stderr, "dw_gui_drawControlDeck() failed: unable to load image\n");
		return;
	}

	// Lock screen surface!!!
	if (SDL_MUSTLOCK(s)) SDL_LockSurface(s);

	// Lock main deck surface
	if (SDL_MUSTLOCK(main_deck)) SDL_LockSurface(main_deck);
	assert(main_deck->w <= s->w && main_deck->h <= s->h);

	// Manage control deck position
	switch (hpos) { // Horizontal coordinates
		case HLeft:
			x_deck_pos = 0;
			break;
		case HRight:
			x_deck_pos = (s->w - main_deck->w) - 1;
			break;
		case HCenter:
		default:
			x_deck_pos = ((s->w - main_deck->w) / 2) - 1;
			break;
	}

	switch (vpos) { // Vertical coordinates
		case VCenter:
			y_deck_pos = ((s->h - main_deck->h) / 2) - 1;
			break;
		case VTop:
			y_deck_pos = 0;
			break;
		case VBottom:
			y_deck_pos = (s->h - main_deck->h) - 1;
		default:
			break;
	}

	src_rect.x = 0; src_rect.y = 0; src_rect.w = main_deck->w; src_rect.h = main_deck->h;
	dst_rect.x = x_deck_pos; dst_rect.y = y_deck_pos; dst_rect.w = main_deck->w; dst_rect.h = main_deck->h;

	SDL_BlitSurface(main_deck, &src_rect, s, &dst_rect);

	// Unlock and free main deck surface
	if (SDL_MUSTLOCK(main_deck)) SDL_UnlockSurface(main_deck);
	SDL_FreeSurface(main_deck);

	// Unlock screen surface!!!
	if (SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);
}
