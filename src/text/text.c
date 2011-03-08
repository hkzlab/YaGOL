#include <SDL/SDL_ttf.h>
#include "text/text.h"

void init_text(void) {
	TTF_Init();
}

void deinit_text(void) {
	TTF_Quit();
}


