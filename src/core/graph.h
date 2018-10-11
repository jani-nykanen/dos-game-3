// Graphics
// (c) 2018 Jani Nykänen

#ifndef __GRAPH__
#define __GRAPH__

#include "bitmap.h"

// Initialize
void init_graphics();

// Clear screen
void clear_screen(char col);

// Draw a bitmap fast
void draw_bitmap_fast(BITMAP* bmp, short dx, short dy);

// Draw a bitmap region fast
void draw_bitmap_region_fast(BITMAP* bmp, short sx, short sy, short sw, short sh,
     short dx, short dy);

// Draw text 
void draw_text(BITMAP* bmp, const char* text, short dx, short dy);

#endif // __GRAPH__
