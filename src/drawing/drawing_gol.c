#include "drawing/drawing.h"
#include "gol/gol.h"

void dw_gol_drawGoLPlane(SDL_Surface *s, Uint16 x, Uint16 y, Uint16 cell_size, Uint32 cell_color) {
	assert(s);
	assert(cell_size);

	Uint16 gol_width = get_gol_grid_width();
	Uint16 gol_height = get_gol_grid_height();
	Uint16 x_pos, y_pos;

	Uint32 color;
	Uint32 col_black;
	SDL_Rect node;

	if (SDL_MUSTLOCK(s)) SDL_LockSurface(s);

	col_black = SDL_MapRGB(s->format, 0, 0, 0);

	for (x_pos = 0; x_pos < gol_width; x_pos++)
		for (y_pos = 0; y_pos < gol_height; y_pos++) {
			if (get_gol_node(x_pos, y_pos))
				color = cell_color;
			else
				color = col_black;

			node.w = node.h = cell_size;
			node.x = x + x_pos * cell_size;
			node.y = y + y_pos * cell_size;

			SDL_FillRect(s, &node, color);
		}

	if (SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);
}
