#ifndef _GRAPROJ_COMMON_DEFS_
#define _GRAPROJ_COMMON_DEFS_

// Include these everywhere...
#include <assert.h>
#include <SDL/SDL.h>

#if 0  // Already included into SDL.h
// Generic type definitions
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;
typedef char Sint8;
typedef short Sint16;
typedef int Sint32;
typedef long long Sint64;
#endif

// Graphical output definitions
#define GRAPH_WIDTH 640
#define GRAPH_HEIGHT 480
#define GRAPH_DEPTH 32

#define DEFAULT_GRID_WIDTH 200
#define DEFAULT_GRID_HEIGHT 130
#define DEFAULT_CELL_SIZE 3 // Cell size in pixels

#endif /* _GRAPROJ_COMMON_DEFS_ */
