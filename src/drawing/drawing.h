#ifndef _YAGOL_DRAWING_HEADER_
#define _YAGOL_DRAWING_HEADER_

#include <SDL/SDL.h>
#include "common/defs.h"

// * BASE DRAWING FUNCTIONS *

Uint32 dw_getPixel(SDL_Surface *s, Uint16 x, Uint16 y);
void dw_setPixel(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y);

void dw_drawHLine(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y, Uint16 len);
void dw_drawVLine(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y, Uint16 len);

void dw_drawBox(SDL_Surface *s, Uint32 color, Uint16 x, Uint16 y, Uint16 h, Uint16 w, Uint16 border);

// * GUI DRAWING FUNCTIONS *
enum HPosition {HTop, HCenter, HBottom};
enum VPosition {VLeft, VCenter, VBottom};

void dw_gui_drawControlDeck(SDL_Surface *s, enum HPosition vpos, enum VPosition hpos);

#endif /* _YAGOL_DRAWING_HEADER_ */
