#include "drawing/drawing.h"
#include "common/endianess.h"

Uint32 dw_getPixel(SDL_Surface *s, Uint16 x, Uint16 y) {
	assert(s);
	assert(x < s->w && y < s->h);

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
	assert(x < s->w && y < s->h);

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

void dw_drawHLine(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y, Uint16 len) {
	assert(s);
	assert(x + len < s->w && y < s->h && len);

	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = len; rect.h = 1;

	SDL_FillRect(s, &rect, color);
}

void dw_drawVLine(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y, Uint16 len) {
	assert(s);
	assert(x < s->w && y + len < s->h && len);

	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = 1; rect.h = len;

	SDL_FillRect(s, &rect, color);	
}

void dw_drawBox(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y, Uint16 h, Uint16 w, Uint16 border) {
	assert(s);
	assert(x + w < s->w && y + h < s->h && h && w);

	while (border--) {
		dw_drawVLine(s, color, x, y, h);
		dw_drawVLine(s, color, x + w, y, h);
		dw_drawHLine(s, color, x, y, w);
		dw_drawHLine(s, color, x, y + h, w);

		x++; y++;
		w--; h--;
	}
}
