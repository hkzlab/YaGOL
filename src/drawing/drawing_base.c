#include "drawing/drawing.h"
#include "common/endianess.h"

Uint32 dw_getPixel(SDL_Surface *s, Uint16 x, Uint16 y) {
	assert(s);
	assert(x < s->w && y < s->h && x >= 0 && y >= 0);

	Uint32 bpp = s->format->BytesPerPixel;
	Uint8 *p =  (Uint8 *)s->pixels + (y * s->pitch) + (x * bpp);
	Uint32 pix;

	switch (bpp) {
		case 1: // b/w
			return *p;
		case 2: // 16 bit per pixel
			return READ_UINT16(p);
		case 3:
			pix = p[0] << 24 | p[1] << 16 | p[0] << 0;
			return READ_UINT32(&pix);
		case 4:
			return READ_UINT32(p);
		default: // !?!?
			return 0;
	}
}

void dw_setPixel(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y) {
	assert(s);
	assert(x < s->w && y < s->h && x >= 0 && y >= 0);

	Uint32 bpp = s->format->BytesPerPixel;
	Uint8 *p =  (Uint8 *)s->pixels + (y * s->pitch) + (x * bpp);
	Uint32 pix;

	switch (bpp) {
		case 1: // b/w
			*p = color & 0xFF;
			break;
		case 2: // 16 bit per pixel
			WRITE_UINT16(p, color & 0xFFFF);
			break;
		case 3:
			WRITE_UINT32(&pix, color);
			p[0] = ((Uint8*)(&pix))[0];
			p[1] = ((Uint8*)(&pix))[1];
			p[2] = ((Uint8*)(&pix))[2];
			break;
		case 4:
			WRITE_UINT32(p, color);
			break;
		default: // !?!?
			return;
	}

}

void dw_drawHLine(SDL_Surface *s, Uint16 x, Uint16 y, Uint16 len) {
	;
}

void dw_drawVLine(SDL_Surface *s, Uint16 x, Uint16 y, Uint16 len) {
	;
}

void dw_drawBox(SDL_Surface *s, Uint16 x, Uint16 y, Uint16 h, Uint16 w, Uint16 border) {
	;
}
