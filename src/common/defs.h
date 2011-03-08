#ifndef _GRAPROJ_COMMON_DEFS_
#define _GRAPROJ_COMMON_DEFS_

// Include these everywhere...
#include <assert.h>

// Generic type definitions
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef char sint8;
typedef short sint16;
typedef int sint32;
typedef long long sint64;

// Graphical output definitions
#define GRAPH_WIDTH 640
#define GRAPH_HEIGHT 480
#define GRAPH_DEPTH 32

#define DEFAULT_GRID_WIDTH 200
#define DEFAULT_GRID_HEIGHT 130
#define DEFAULT_CELL_SIZE 3 // Cell size in pixels

#endif /* _GRAPROJ_COMMON_DEFS_ */
