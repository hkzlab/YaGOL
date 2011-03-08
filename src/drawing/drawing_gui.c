#include "drawing/drawing.h"
#include <SDL/SDL_image.h>

#define CONTROL_DECK "src/resources/control_deck.png"
#define DECK_LOGO "src/resources/deck_logo.png"
#define CHAOS_BUTTON "src/resources/chaos_button.png"
#define FASTF_BUTTON "src/resources/fastf_button.png"
#define QUIT_BUTTON "src/resources/quit_button.png"
#define START_BUTTON "src/resources/start_button.png"
#define STEP_BUTTON "src/resources/step_button.png"
#define STOP_BUTTON "src/resources/stop_button.png"

extern Uint16 all_button_y, chaos_button_x, fastf_button_x, quit_button_x, start_button_x, step_button_x, stop_button_x;

void dw_gui_private_drawFullImage(SDL_Surface *s, char *imagepath, Uint16 x, Uint16 y);

void dw_gui_drawControlDeck(SDL_Surface *s, enum HPosition hpos, enum VPosition vpos) {
	assert(s);

	Uint16 x_deck_pos, y_deck_pos, x_button_pos, y_button_pos;
	SDL_Rect src_rect, dst_rect;
	SDL_Surface *button;
	SDL_Surface *main_deck = IMG_Load(CONTROL_DECK);

	if (!main_deck) {
		fprintf(stderr, "dw_gui_drawControlDeck() failed: unable to load %s image\n", CONTROL_DECK);
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

	// Time to draw the BUTTONS!
	y_button_pos = y_deck_pos + 4;
	x_button_pos = x_deck_pos + 4;

	all_button_y = y_button_pos;

	// START button
	start_button_x = x_button_pos;
	dw_gui_private_drawFullImage(s, START_BUTTON, x_button_pos, y_button_pos);

	// STEP button
	x_button_pos += BUTTON_WIDTH + 3;
	step_button_x = x_button_pos;
	dw_gui_private_drawFullImage(s, STEP_BUTTON, x_button_pos, y_button_pos);

	// FASTF button
	x_button_pos += BUTTON_WIDTH + 3;
	fastf_button_x = x_button_pos;
	dw_gui_private_drawFullImage(s, FASTF_BUTTON, x_button_pos, y_button_pos);

	// STOP button
	x_button_pos += BUTTON_WIDTH + 3;
	stop_button_x = x_button_pos;
	dw_gui_private_drawFullImage(s, STOP_BUTTON, x_button_pos, y_button_pos);

	// QUIT button
	x_button_pos = (x_deck_pos + main_deck->w) - 4 - BUTTON_WIDTH;
	quit_button_x = x_button_pos;
	dw_gui_private_drawFullImage(s, QUIT_BUTTON, x_button_pos, y_button_pos);

	// CHAOS button
	x_button_pos -= BUTTON_WIDTH + 3;
	chaos_button_x = x_button_pos;
	dw_gui_private_drawFullImage(s, CHAOS_BUTTON, x_button_pos, y_button_pos);

	// DECK LOGO!
	x_button_pos -= 70 ;
	dw_gui_private_drawFullImage(s, DECK_LOGO, x_button_pos, y_button_pos);


	// Unlock and free main deck surface
	if (SDL_MUSTLOCK(main_deck)) SDL_UnlockSurface(main_deck);
	SDL_FreeSurface(main_deck);

	// Unlock screen surface!!!
	if (SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);
}

void dw_gui_private_drawFullImage(SDL_Surface *s, char *imagepath, Uint16 x, Uint16 y) {
	assert(s);
	assert(imagepath);

	SDL_Surface *img;
	SDL_Rect dst_rect, src_rect;

	img = IMG_Load(imagepath);
	if (!img) {
		fprintf(stderr, "dw_gui_private_drawFullImage() failed: unable to load %s image\n", imagepath);
		return;		
	}

	if (SDL_MUSTLOCK(img)) SDL_LockSurface(img);
	src_rect.x = 0; src_rect.y = 0; src_rect.w = img->w; src_rect.h = img->h;
	dst_rect.x = x; dst_rect.y = y; dst_rect.w = img->w; dst_rect.h = img->h;
	SDL_BlitSurface(img, &src_rect, s, &dst_rect);

	if (SDL_MUSTLOCK(img)) SDL_UnlockSurface(img);

	SDL_FreeSurface(img);
}
