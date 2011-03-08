#include <SDL/SDL_ttf.h>
#include "text/text.h"

#define FONT_RESOURCE "src/resources/FreeMono.ttf"
#define FONT_SIZE 8

static TTF_Font *font;

void init_text(void) {
	TTF_Init();

	font = TTF_OpenFont(FONT_RESOURCE, FONT_SIZE);

	if(!font)
		fprintf(stderr, "init_text() failed: unable to open %s\n", FONT_RESOURCE);
}

void deinit_text(void) {
	TTF_CloseFont(font);
	TTF_Quit();
}

void print_text_simple(SDL_Surface *s, char *text, Uint16 x, Uint16 y) {
	SDL_Color col;
	col.r = 200; col.g = 200; col.b = 200;

	SDL_Surface *txt = TTF_RenderText_Solid(font, text, col);

	SDL_Rect src, dest;

	if (SDL_MUSTLOCK(txt)) SDL_LockSurface(txt);
	src.x = src.y = 0;
	src.w = txt->w; src.h = txt->h;

	dest.x = x; dest.y = y;
	dest.w = txt->w; dest.h = txt->h;

	if (SDL_MUSTLOCK(s)) SDL_LockSurface(s);
	SDL_BlitSurface(txt, &src, s, &dest);
	if (SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);

	if (SDL_MUSTLOCK(txt)) SDL_UnlockSurface(txt);

	SDL_FreeSurface(txt);
}

