#ifndef _TEXT_HEADER_
#define _TEXT_HEADER_

#include "common/defs.h"

void init_text(void);
void deinit_text(void);

void print_text_simple(SDL_Surface *s, char *text, Uint16 x, Uint16 y);

#endif /* _TEXT_HEADER_ */
