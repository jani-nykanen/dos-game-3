// Graphics
// (c) 2018 Jani Nykänen

#ifndef __GRAPH__
#define __GRAPH__

#include "bitmap.h"

// Flipping flags
enum {

    FLIP_NONE = 0,
    FLIP_H = 1,
    FLIP_V = 2,
    FLIP_BOTH = 3,
};

// Initialize
void init_graphics();

// Clear screen
void clear_screen(char col);

// Draw a bitmap fast
void draw_bitmap_fast(BITMAP* bmp, short dx, short dy);

// Draw a bitmap region fast
void draw_bitmap_region_fast(BITMAP* bmp, short sx, short sy, short sw, short sh,
     short dx, short dy);

// Draw bitmap
void draw_bitmap(BITMAP* bmp, short dx, short dy, char flip);

// Draw a bitmap region
void draw_bitmap_region(BITMAP* bmp, short sx, short sy, short sw, short sh,
     short dx, short dy, char flip);

// Draw text 
void draw_text(BITMAP* bmp, const char* text, short dx, short dy);

// Draw a filled rectangle
void fill_rect(short dx, short dy, short dw, short dh, char col);

// Set render target
void set_render_target(BITMAP* bmp);

#endif // __GRAPH__
