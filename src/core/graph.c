// Graphics
// (c) 2018 Jani Nykänen

#include "graph.h"

#include <dos.h>
#include <conio.h>
#include <graph.h>

#include "stdbool.h"
#include "string.h"
#include "stdio.h"

#include "palette.c"


// VGA position
static const long VGA_POS = 0xA0000000;

// Palette constants
static const long PALETTE_INDEX = 0x03c8;
static const long PALETTE_DATA = 0x03c9;


// Set palette
static void set_palette() {

    short i = 0;

    // Set palette
    outp(PALETTE_INDEX,0);

    for(i = 0; i < 256*3 ;  ++ i) {

        outp(PALETTE_DATA, palette[i]/4);
    }
}


// Initialize
void init_graphics() {

    // Set video mode to 320x200 256 colors
    _setvideomode(_MRES256COLOR);

    // Set palette
    set_palette();
}


// Clear screen
void clear_screen(char col) {

    char* VGA = (char*)VGA_POS;   

    memset(VGA, col, 320*200);
}


// Draw a bitmap fast
void draw_bitmap_fast(BITMAP* bmp, short dx, short dy) {

    char* VGA = (char*)VGA_POS; 
    char* data = (char*)bmp->data;
    short y = 0;
    short offset = 320*dy + dx;
    short bmp_off = 0;

    for(; y < bmp->h; ++ y) {

        memcpy(VGA + offset, data + bmp_off, bmp->w);
        offset += 320;
        bmp_off += bmp->w;
    }
}


// Draw a bitmap region fast
void draw_bitmap_region_fast(BITMAP* bmp, short sx, short sy, short sw, short sh,
     short dx, short dy) {

    char* VGA = (char*)VGA_POS; 
    char* data = (char*)bmp->data;
    short y;
    short offset = 320*dy + dx;
    short bmp_off = bmp->w*sy + sx;

    for(y=0; y < sh; ++ y) {

        memcpy(VGA + offset, data + bmp_off, sw);
        offset += 320;
        bmp_off += bmp->w;
    }
}


// Draw text 
void draw_text(BITMAP* bmp, const char* text, 
    short dx, short dy) {
    
    char len = strlen((const char*)text);

    short x = dx;
    short y = dy;
    short cw = bmp->w / 16;
    short ch = cw;
    short i=0;
    char c;
    short sx;
    short sy;

    for(; i < len; ++ i) {

        c = text[i];
        if(c > 0) -- c;
        sx = c % 16;
        sy = c / 16;

        draw_bitmap_region_fast(bmp,sx*cw,sy*ch,cw,ch,x,y);

        x += cw;
    }
}
